#!/usr/bin/env python
'''
Description:
This scipt plots the TH1 histograms that compare EWK with QCD shapes, 
for Baseline and Inverted analysis modes.

For the definition of the counter class see:
HiggsAnalysis/NtupleAnalysis/scripts

For more counter tricks and optios see also:
HiggsAnalysis/NtupleAnalysis/scripts/hplusPrintCounters.py

Usage:
./test.py -m <pseudo_mcrab_directory> [opts]

Examples:
./test.py -m FakeBMeasurement_170701_084855 --mergeEWK -e "Charged|QCD_HT50to100|QCD_HT100to200|QCD_HT200to300|QCD-b" -o 'OptNumberOfBJetsCutDirection>=ChiSqrCutValue100NumberOfBJetsCutValue1'
./test.py -m FakeBMeasurement_170701_084855 --mergeEWK -e "Charged|QCD_HT" -o 'OptNumberOfBJetsCutDirection>=ChiSqrCutValue100NumberOfBJetsCutValue1'
'''

#================================================================================================ 
# Imports
#================================================================================================ 
import sys
import math
import copy
import os
from optparse import OptionParser

import ROOT
ROOT.gROOT.SetBatch(True)
from ROOT import *

import HiggsAnalysis.NtupleAnalysis.tools.dataset as dataset
import HiggsAnalysis.NtupleAnalysis.tools.histograms as histograms
import HiggsAnalysis.NtupleAnalysis.tools.counter as counter
import HiggsAnalysis.NtupleAnalysis.tools.tdrstyle as tdrstyle
import HiggsAnalysis.NtupleAnalysis.tools.styles as styles
import HiggsAnalysis.NtupleAnalysis.tools.plots as plots
import HiggsAnalysis.NtupleAnalysis.tools.crosssection as xsect
import HiggsAnalysis.NtupleAnalysis.tools.multicrabConsistencyCheck as consistencyCheck

#================================================================================================ 
# Function Definition
#================================================================================================ 
def Print(msg, printHeader=False):
    fName = __file__.split("/")[-1]
    if printHeader==True:
        print "=== ", fName
        print "\t", msg
    else:
        print "\t", msg
    return


def Verbose(msg, printHeader=True, verbose=False):
    if not opts.verbose:
        return
    Print(msg, printHeader)
    return


def GetLumi(datasetsMgr):
    Verbose("Determininig Integrated Luminosity")
    
    lumi = 0.0
    for d in datasetsMgr.getAllDatasets():
        if d.isMC():
            continue
        else:
            lumi += d.getLuminosity()
    Verbose("Luminosity = %s (pb)" % (lumi), True)
    return lumi


def GetListOfEwkDatasets():
    Verbose("Getting list of EWK datasets")
    return ["TT", "WJetsToQQ_HT_600ToInf", "DYJetsToQQHT", "SingleTop", "TTWJetsToQQ", "TTZToQQ", "Diboson", "TTTT"]


def GetHistoKwargs(histoName):
    '''
    '''
    Verbose("Creating a map of histoName <-> kwargs")

    _opts   = {}
    _xlabel = None

    if "tetrajetm" in histoName.lower():
        _rebin  = 5
        _units  = "GeV/c^{2}"
        _format = "%0.0f GeV/c^{2}"
        _xlabel = "m_{jjjb} (%s)" % (_units)
        _logY   = True
        _cutBox = {"cutValue": 173.21, "fillColor": 16, "box": False, "line": True, "greaterThan": True}
        _opts["xmax"] = 2000.0
    elif "trijetm" in histoName.lower():
        _rebin  = 1
        _units  = "GeV/c^{2}"
        _format = "%0.0f " + _units
        _xlabel = "m_{jjb} (%s)" % _units
        _logY   = False #True #alex
        _cutBox = {"cutValue": 173.21, "fillColor": 16, "box": False, "line": True, "greaterThan": True}
        _opts["xmax"] = 800.0
    else:
        raise Exception("The kwargs have not been prepared for the histogram with name \"%s\"." % (histoName) )

    # Customise options (main pad) for with/whitout logY scale 
    if _logY:
        _opts["ymin"] = 2e-4
        _opts["ymaxfactor"] = 10
    else:
        _opts["ymin"] = 0.0
        _opts["ymaxfactor"] = 1.2

    # Draw the histograms
    if "trijetmass" in histoName.lower():
        _opts["xmax"] = 800.0

    # Define plotting options    
    kwargs = {
        "xlabel": _xlabel,
        "ylabel": "Arbitrary Units / %s" % (_format),
        "log"   : _logY,
        "opts"  : _opts,
        "opts2" : {"ymin": 0.0, "ymax": 2.0},
        "rebinX": _rebin,
        "ratio" : True, 
        "cutBox": _cutBox,
        "cmsExtraText": "Preliminary",
        "ratioYlabel" : "Ratio",
        "ratioInvert" : False, 
        "addCmsText"  : True,
        "createLegend": {"x1": 0.62, "y1": 0.78, "x2": 0.92, "y2": 0.92},
               }
    return kwargs


def GetHistoList(analysisType="Inverted", bType=""):
    Verbose("Creating purity histo list  for %s" % analysisType)

    IsBaselineOrInverted(analysisType)

    bTypes = ["", "EWKFakeB", "EWKGenuineB"]
    if bType not in bTypes:
        raise Exception("Invalid analysis type \"%s\". Please select one of the following: %s" % (bType, "\"" + "\", \"".join(bTypes) + "\"") )

    histoList = []
    folder    = "ForFakeBMeasurement" + bType
    histoList.append("%s/%s_TopMassReco_LdgTrijetM_AfterAllSelections" % (folder, analysisType) )
    #histoList.append("%s/%s_TopMassReco_LdgTetrajetMass_AfterAllSelections" % (folder, analysisType) )
    if 0:
        histoList.append("%s/%s_TopMassReco_SubldgTetrajetMass_AfterAllSelections" % (folder, analysisType) )
        histoList.append("%s/%s_TopMassReco_SubLdgTrijetM_AfterAllSelections" % (folder, analysisType) )
        histoList.append("%s/%s_TopMassReco_LdgDijetM_AfterAllSelections" % (folder, analysisType) )
        histoList.append("%s/%s_TopMassReco_SubLdgDijetM_AfterAllSelections" % (folder, analysisType) )
    return histoList

def GetDatasetsFromDir(opts):
    Verbose("Getting datasets")
    
    if (not opts.includeOnlyTasks and not opts.excludeTasks):
        datasets = dataset.getDatasetsFromMulticrabDirs([opts.mcrab],
                                                        dataEra=opts.dataEra,
                                                        searchMode=opts.searchMode, 
                                                        analysisName=opts.analysisName,
                                                        optimizationMode=opts.optMode)
    elif (opts.includeOnlyTasks):
        datasets = dataset.getDatasetsFromMulticrabDirs([opts.mcrab],
                                                        dataEra=opts.dataEra,
                                                        searchMode=opts.searchMode,
                                                        analysisName=opts.analysisName,
                                                        includeOnlyTasks=opts.includeOnlyTasks,
                                                        optimizationMode=opts.optMode)
    elif (opts.excludeTasks):
        datasets = dataset.getDatasetsFromMulticrabDirs([opts.mcrab],
                                                        dataEra=opts.dataEra,
                                                        searchMode=opts.searchMode,
                                                        analysisName=opts.analysisName,
                                                        excludeTasks=opts.excludeTasks,
                                                        optimizationMode=opts.optMode)
    else:
        raise Exception("This should never be reached")
    return datasets
    

def main(opts):
    
    #optModes = ["", "OptChiSqrCutValue40", "OptChiSqrCutValue60", "OptChiSqrCutValue80", "OptChiSqrCutValue100", "OptChiSqrCutValue120", "OptChiSqrCutValue140"] 
    #optModes = ["OptChiSqrCutValue250", "OptChiSqrCutValue150", "OptChiSqrCutValue200", "OptChiSqrCutValue180", "OptChiSqrCutValue300"]
    #optModes = ["", "OptChiSqrCutValue50p0", "OptChiSqrCutValue100p0", "OptChiSqrCutValue150p0", "OptChiSqrCutValue200p0"]
    optModes = ["OptChiSqrCutValue100"]

    if opts.optMode != None:
        optModes = [opts.optMode]
        
    # For-loop: All opt Mode
    for opt in optModes:
        opts.optMode = opt

        # Setup & configure the dataset manager 
        datasetsMgr = GetDatasetsFromDir(opts)
        datasetsMgr.updateNAllEventsToPUWeighted()
        datasetsMgr.loadLuminosities() # from lumi.json
        if opts.verbose:
            datasetsMgr.PrintCrossSections()
            datasetsMgr.PrintLuminosities()

        if 0:
            datasetsMgr.remove(filter(lambda name: "ST" in name, datasetsMgr.getAllDatasetNames()))
               
        # Merge histograms (see NtupleAnalysis/python/tools/plots.py) 
        plots.mergeRenameReorderForDataMC(datasetsMgr) 
   
        # Get Integrated Luminosity
        if 0:
            datasetsMgr.remove(filter(lambda name: "Data" in name, datasetsMgr.getAllDatasetNames()))

        # Re-order datasets (different for inverted than default=baseline)
        if 0:
            newOrder = ["Data"]
            newOrder.extend(GetListOfEwkDatasets())
            datasetsMgr.selectAndReorder(newOrder)

        # Set/Overwrite cross-sections
        for d in datasetsMgr.getAllDatasets():
            if "ChargedHiggs" in d.getName():
                datasetsMgr.getDataset(d.getName()).setCrossSection(1.0)

        # Merge EWK samples
        if opts.mergeEWK:
            datasetsMgr.merge("EWK", GetListOfEwkDatasets())
            plots._plotStyles["EWK"] = styles.getAltEWKStyle()
        else:
            Print("Cannot draw the histograms without the option --mergeEWK. Exit", True)            
                    
        # Print dataset information
        datasetsMgr.PrintInfo()

        # Apply TDR style
        style = tdrstyle.TDRStyle()
        style.setOptStat(True)

        # Do the template comparisons
        for hName in GetHistoList(analysisType="Inverted", bType=""):
            PlotTemplates(datasetsMgr, hName, analysisType="Inverted")
    return

def getHistos(datasetsMgr, datasetName, name1, name2):
    Verbose("getHistos()", True)

    h1 = datasetsMgr.getDataset(datasetName).getDatasetRootHisto(name1)
    h1.setName("Baseline-" + datasetName)

    h2 = datasetsMgr.getDataset(datasetName).getDatasetRootHisto(name2)
    h2.setName("Inverted-" + datasetName)
    return [h1, h2]


def getHisto(datasetsMgr, datasetName, histoName, analysisType):
    Verbose("getHisto()", True)

    h1 = datasetsMgr.getDataset(datasetName).getDatasetRootHisto(histoName)
    h1.setName(analysisType + "-" + datasetName)
    return h1


def PlotTemplates(datasetsMgr, histoName, analysisType="Inverted"):                  
    Verbose("Plotting EWK Vs QCD unity-normalised histograms")

    # Create comparison plot
    p1 = plots.ComparisonPlot(
        getHisto(datasetsMgr, "Data", histoName, "Baseline"),
        getHisto(datasetsMgr, "Data", histoName, "Inverted")
        )
    p1.histoMgr.normalizeMCToLuminosity(datasetsMgr.getDataset("Data").getLuminosity())
    
    defaultFolder  = "ForFakeBMeasurement"
    genuineBFolder = defaultFolder + "EWKGenuineB"
    fakeBFolder    = defaultFolder + "EWKFakeB"
    histoNameNew   = histoName.replace( defaultFolder, genuineBFolder)
    p2 = plots.ComparisonPlot(
        getHisto(datasetsMgr, "EWK", histoNameNew, "Baseline"),
        getHisto(datasetsMgr, "EWK", histoNameNew, "Inverted")
        )
    p2.histoMgr.normalizeMCToLuminosity(datasetsMgr.getDataset("Data").getLuminosity())

    p3 = plots.ComparisonPlot(
        getHisto(datasetsMgr, "QCD", histoNameNew, "Baseline"), #QCD-b
        getHisto(datasetsMgr, "QCD", histoNameNew, "Inverted")  #QCD-b
        )
    p3.histoMgr.normalizeMCToLuminosity(datasetsMgr.getDataset("Data").getLuminosity())

    # Get EWKGenuineB histos
    EWKGenuineB_baseline = p2.histoMgr.getHisto("Baseline-EWK").getRootHisto().Clone("Baseline-EWKGenuineB")
    EWKGenuineB_inverted = p2.histoMgr.getHisto("Inverted-EWK").getRootHisto().Clone("Inverted-EWKGenuineB")

    QCDGenuineB_baseline = p3.histoMgr.getHisto("Baseline-QCD").getRootHisto().Clone("Baseline-QCDGenuineB") # QCD-b
    QCDGenuineB_inverted = p3.histoMgr.getHisto("Inverted-QCD").getRootHisto().Clone("Inverted-QCDGenuineB") # QCD-b

    # Get FakeB histos
    Data_baseline = p1.histoMgr.getHisto("Baseline-Data").getRootHisto().Clone("Baseline-FakeB")
    #Data_baseline.Add(EWKGenuineB_baseline, -1)
    Data_inverted = p1.histoMgr.getHisto("Inverted-Data").getRootHisto().Clone("Inverted-FakeB")
    #Data_inverted.Add(EWKGenuineB_inverted, -1)

    # Normalize histograms to unit area
    if 1:
        EWKGenuineB_baseline.Scale(1.0/EWKGenuineB_baseline.Integral())
        EWKGenuineB_inverted.Scale(1.0/EWKGenuineB_inverted.Integral())
        QCDGenuineB_baseline.Scale(1.0/QCDGenuineB_baseline.Integral())    
        QCDGenuineB_inverted.Scale(1.0/QCDGenuineB_inverted.Integral())
        Data_baseline.Scale(1.0/Data_baseline.Integral())
        Data_inverted.Scale(1.0/Data_inverted.Integral())

    # Create the final plot object
    comparisonList = [EWKGenuineB_inverted, QCDGenuineB_inverted]
    p = plots.ComparisonManyPlot(Data_inverted, comparisonList, saveFormats=[])
    p.setLuminosity(GetLumi(datasetsMgr))
        
    # Apply styles
    p.histoMgr.forHisto("Inverted-EWKGenuineB", styles.getBaselineStyle() )
    p.histoMgr.forHisto("Inverted-FakeB"      , styles.getDataStyle() )
    p.histoMgr.forHisto("Inverted-QCDGenuineB", styles.getQCDLineStyle() )

    # Set draw style
    p.histoMgr.setHistoDrawStyle("Inverted-EWKGenuineB", "AP")
    p.histoMgr.setHistoDrawStyle("Inverted-FakeB"      , "AP")
    p.histoMgr.setHistoDrawStyle("Inverted-QCDGenuineB", "AP")

    # Set legend style
    p.histoMgr.setHistoLegendStyle("Inverted-EWKGenuineB", "LP")
    p.histoMgr.setHistoLegendStyle("Inverted-FakeB"      , "LP")
    p.histoMgr.setHistoLegendStyle("Inverted-QCDGenuineB", "LP")

    # Set legend labels
    p.histoMgr.setHistoLegendLabelMany({
            "Inverted-EWKGenuineB": "GenuineB (EWK)",
            "Inverted-QCDGenuineB": "GenuineB (QCD)",
            "Inverted-FakeB"      : "Data",
            })

    # Append analysisType to histogram name
    saveName = histoName

    # Draw the histograms #alex
    plots.drawPlot(p, saveName, **GetHistoKwargs(histoName) ) #the "**" unpacks the kwargs_ 

    # _kwargs = {"lessThan": True}
    # p.addCutBoxAndLine(cutValue=200, fillColor=ROOT.kRed, box=False, line=True, ***_kwargs)
    
    # Add text
    # OptNumberOfBJetsCutDirection>=ChiSqrCutValue100NumberOfBJetsCutValue1
    text = opts.optMode.replace("OptNumberOfBJetsCutDirection>=", "BJets #geq").replace("ChiSqrCutValue100NumberOfBJetsCutValue", "")
    histograms.addText(0.21, 0.85, text)

    # Save plot in all formats
    saveDir = os.path.join(opts.saveDir, "Templates", opts.optMode)
    SavePlot(p, saveName, saveDir, saveFormats = [".C", ".png", ".pdf"])
    return


def IsBaselineOrInverted(analysisType):
    analysisTypes = ["Baseline", "Inverted"]
    if analysisType not in analysisTypes:
        raise Exception("Invalid analysis type \"%s\". Please select one of the following: %s" % (analysisType, "\"" + "\", \"".join(analysisTypes) + "\"") )
    else:
        pass
    return

def SavePlot(plot, plotName, saveDir, saveFormats = [".C", ".png", ".pdf"]):
    Verbose("Saving the plot in %s formats: %s" % (len(saveFormats), ", ".join(saveFormats) ) )

    # Check that path exists
    if not os.path.exists(saveDir):
        os.makedirs(saveDir)

    # Create the name under which plot will be saved
    saveName = os.path.join(saveDir, plotName.replace("/", "_"))

    # For-loop: All save formats
    for i, ext in enumerate(saveFormats):
        saveNameURL = saveName + ext
        saveNameURL = saveNameURL.replace("/publicweb/a/aattikis/", "http://home.fnal.gov/~aattikis/")
        if opts.url:
            Print(saveNameURL, i==0)
        else:
            Print(saveName + ext, i==0)
        plot.saveAs(saveName, formats=saveFormats)
    return


#================================================================================================ 
# Main
#================================================================================================ 
if __name__ == "__main__":
    '''
    https://docs.python.org/3/library/argparse.html
 
    name or flags...: Either a name or a list of option strings, e.g. foo or -f, --foo.
    action..........: The basic type of action to be taken when this argument is encountered at the command line.
    nargs...........: The number of command-line arguments that should be consumed.
    const...........: A constant value required by some action and nargs selections.
    default.........: The value produced if the argument is absent from the command line.
    type............: The type to which the command-line argument should be converted.
    choices.........: A container of the allowable values for the argument.
    required........: Whether or not the command-line option may be omitted (optionals only).
    help............: A brief description of what the argument does.
    metavar.........: A name for the argument in usage messages.
    dest............: The name of the attribute to be added to the object returned by parse_args().
    '''
    
    # Default Settings
    ANALYSISNAME = "FakeBMeasurement"
    SEARCHMODE   = "80to1000"
    DATAERA      = "Run2016"
    OPTMODE      = None
    BATCHMODE    = True
    PRECISION    = 3
    INTLUMI      = -1.0
    SUBCOUNTERS  = False
    LATEX        = False
    MCONLY       = False
    MERGEEWK     = False
    URL          = False
    NOERROR      = True
    SAVEDIR      = "/publicweb/a/aattikis/FakeBMeasurement/"
    VERBOSE      = False
    HISTOLEVEL   = "Vital" # 'Vital' , 'Informative' , 'Debug'

    # Define the available script options
    parser = OptionParser(usage="Usage: %prog [options]")

    parser.add_option("-m", "--mcrab", dest="mcrab", action="store", 
                      help="Path to the multicrab directory for input")

    parser.add_option("-o", "--optMode", dest="optMode", type="string", default=OPTMODE, 
                      help="The optimization mode when analysis variation is enabled  [default: %s]" % OPTMODE)

    parser.add_option("-b", "--batchMode", dest="batchMode", action="store_false", default=BATCHMODE, 
                      help="Enables batch mode (canvas creation does NOT generate a window) [default: %s]" % BATCHMODE)

    parser.add_option("--analysisName", dest="analysisName", type="string", default=ANALYSISNAME,
                      help="Override default analysisName [default: %s]" % ANALYSISNAME)

    parser.add_option("--mcOnly", dest="mcOnly", action="store_true", default=MCONLY,
                      help="Plot only MC info [default: %s]" % MCONLY)

    parser.add_option("--intLumi", dest="intLumi", type=float, default=INTLUMI,
                      help="Override the integrated lumi [default: %s]" % INTLUMI)

    parser.add_option("--searchMode", dest="searchMode", type="string", default=SEARCHMODE,
                      help="Override default searchMode [default: %s]" % SEARCHMODE)

    parser.add_option("--dataEra", dest="dataEra", type="string", default=DATAERA, 
                      help="Override default dataEra [default: %s]" % DATAERA)

    parser.add_option("--mergeEWK", dest="mergeEWK", action="store_true", default=MERGEEWK, 
                      help="Merge all EWK samples into a single sample called \"EWK\" [default: %s]" % MERGEEWK)

    parser.add_option("--saveDir", dest="saveDir", type="string", default=SAVEDIR, 
                      help="Directory where all pltos will be saved [default: %s]" % SAVEDIR)

    parser.add_option("--url", dest="url", action="store_true", default=URL, 
                      help="Don't print the actual save path the histogram is saved, but print the URL instead [default: %s]" % URL)
    
    parser.add_option("-v", "--verbose", dest="verbose", action="store_true", default=VERBOSE, 
                      help="Enables verbose mode (for debugging purposes) [default: %s]" % VERBOSE)

    parser.add_option("--histoLevel", dest="histoLevel", action="store", default = HISTOLEVEL,
                      help="Histogram ambient level (default: %s)" % (HISTOLEVEL))

    parser.add_option("-i", "--includeOnlyTasks", dest="includeOnlyTasks", action="store", 
                      help="List of datasets in mcrab to include")

    parser.add_option("-e", "--excludeTasks", dest="excludeTasks", action="store", 
                      help="List of datasets in mcrab to exclude")

    (opts, parseArgs) = parser.parse_args()

    # Require at least two arguments (script-name, path to multicrab)
    if len(sys.argv) < 2:
        parser.print_help()
        sys.exit(1)

    if opts.mcrab == None:
        Print("Not enough arguments passed to script execution. Printing docstring & EXIT.")
        parser.print_help()
        #print __doc__
        sys.exit(1)

    # Call the main function
    main(opts)

    if not opts.batchMode:
        raw_input("=== plotFakeB_Templates.py: Press any key to quit ROOT ...")
