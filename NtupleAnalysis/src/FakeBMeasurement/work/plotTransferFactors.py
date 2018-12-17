#!/usr/bin/env python
'''
DESCRIPTION:
This script loads and plots the transfer-factors of the Fake-b measurement (R_i) 
for all the bins considered onto a signle TGraphAsymmetry object


USAGE:
plotTransferFactors.py [opts]


EXAMPLES:
./plotTransferFactors.py -m FakeBMeasurement_Test_22Nov2018/ --gridX --gridY --url
./plotTransferFactors.py -m FakeBMeasurement_Test_22Nov2018/ --gridX --gridY --refHisto "Run2016DE"


LAST USED:
./plotTransferFactors.py -m FakeBMeasurement_Test_22Nov2018/ --gridX --gridY --refHisto "Run2016"

'''

#================================================================================================
# Import modules
#================================================================================================
import re
import os
import getpass
import sys
import imp
import copy
from optparse import OptionParser
import array

import ROOT
ROOT.gROOT.SetBatch(True)
ROOT.PyConfig.IgnoreCommandLineOptions = True

import HiggsAnalysis.NtupleAnalysis.tools.dataset as dataset
import HiggsAnalysis.NtupleAnalysis.tools.histograms as histograms
import HiggsAnalysis.NtupleAnalysis.tools.tdrstyle as tdrstyle
import HiggsAnalysis.NtupleAnalysis.tools.plots as plots
import HiggsAnalysis.NtupleAnalysis.tools.styles as styles
import HiggsAnalysis.NtupleAnalysis.tools.aux as aux
import HiggsAnalysis.NtupleAnalysis.tools.ShellStyles as ShellStyles

#================================================================================================                                                                                                                                 
# Variable definition
#================================================================================================ 
ss = ShellStyles.SuccessStyle()
ns = ShellStyles.NormalStyle()
ts = ShellStyles.NoteStyle()
hs = ShellStyles.HighlightAltStyle()
ls = ShellStyles.HighlightStyle()
es = ShellStyles.ErrorStyle()
cs = ShellStyles.CaptionStyle()

#================================================================================================
# Function definition
#================================================================================================
def Verbose(msg, printHeader=False):
    '''
    Calls Print() only if verbose options is set to true.
    '''
    if not opts.verbose:
        return
    Print(msg, printHeader)
    return


def Print(msg, printHeader=True):
    '''
    Simple print function. If verbose option is enabled prints, otherwise does nothing.
    '''
    fName = __file__.split("/")[-1]
    if printHeader:
        print "=== ", fName
    print "\t", msg
    return

def divideGraph(num, denom, errorY=True, percentDiff=False, invRatio=False):
    '''                                                                                                                                                                                                                           
    Divide two TGraphs
     \param num    Numerator TGraph
     \param denom  Denominator TGraph
     \return new TGraph as the ratio of the two TGraphs
     '''
    gr = copy.deepcopy(num.getRootGraph())

    # Numerator and Denominator graphs are the same (i.e. reference histo)
    if num == denom:
        for i in xrange(gr.GetN()):
            gr.SetPoint(i, gr.GetX()[i], 1.0)
            gr.SetPointEYhigh(i, 1e-4) 
            gr.SetPointEYlow(i , 1e-4)
            # Debug?
            if 0:
                Print("x = %0.3f, y = %.3f" % (gr.GetX()[i], gr.GetY()[i]), i==1)
        return gr

    # For-loop: All points
    for i in xrange(gr.GetN()):
        yDiv = 0
        yVal = denom.getRootGraph().GetY()[i]
        if percentDiff:
            yVal -= num.getRootGraph().GetY()[i]

        # Sanity check
        if yVal > 0:
            yDiv = gr.GetY()[i]/yVal
            if invRatio:
                yDiv = 1.0/yDiv

        # Set new point x-y coords
        gr.SetPoint(i, gr.GetX()[i], yDiv)
        
        # Disable error bars?
        if not errorY:
            gr.SetPointEYlow(i , yVal*1e-4)
            gr.SetPointEYhigh(i, yVal*1e-4)
    return gr

def atoi(text):
    return int(text) if text.isdigit() else text

def natural_keys(text):
    return [ atoi(c) for c in re.split('(\d+)', text) ]

def GetDatasetsFromDir(opts):
    
    datasets = dataset.getDatasetsFromMulticrabDirs([opts.mcrab],
                                                    dataEra=opts.dataEra,
                                                    searchMode=opts.searchMode, 
                                                    analysisName=opts.analysisName,
                                                    optimizationMode=opts.optMode)
    return datasets

def main(opts):

    # Apply TDR style
    style = tdrstyle.TDRStyle()
    style.setOptStat(False)
    style.setGridX(opts.gridX)
    style.setGridY(opts.gridY)
    style.setLogX(opts.logX)
    style.setLogY(opts.logY)
    
    # Setup & configure the dataset manager 
    datasetsMgr = GetDatasetsFromDir(opts)
    datasetsMgr.updateNAllEventsToPUWeighted()
    datasetsMgr.loadLuminosities() # from lumi.json
    plots.mergeRenameReorderForDataMC(datasetsMgr) 
    opts.intLumi = datasetsMgr.getDataset("Data").getLuminosity()

    # Do the plot
    moduleDict  = {}
    moduleNames = list(filter(lambda x: "FakeBTransferFactors" in x and x.endswith(".py") and not x.startswith("#"), os.listdir(opts.mcrab)))
    sKeys = []
    Verbose("Found %d import files:%s%s%s" % (len(moduleNames), hs, "\n\t" + "\n\t".join(moduleNames), ns), True)

    # For-loop: All module files to be imported
    for i,m in enumerate(moduleNames, 1):
        if not opts.verbose:
            Print("Importing module %s" % (hs + os.path.join(opts.mcrab, m) + ns), i==1)
        else:
            Print("Importing module %s" % (hs + os.path.join(opts.mcrab, m) + ns), True)

        # Define the path to the .py file (module Path) and the name to be imported as (module name)
        mPath = os.path.join(os.getcwd(), opts.mcrab, m)
        mName = m.split("_")[-1].replace(".py", "")
        sKeys.append(mName)
        mObj  = imp.load_source(mName, mPath )
        moduleDict[mName] = mObj

        # Debugging
        Verbose(moduleDict[mName].FakeBNormalisation_Value.keys(), False)
        Verbose(moduleDict[mName].FakeBNormalisation_Value.values(), False)
    
    gList  = []
    gListR = []
    # For-loop: All modules imported
    for i, k in enumerate(sKeys, 0):
        g = PlotTFs(i, k, moduleDict[k])
        gList.extend(g)
        gListR.extend(g)

    # Make sure you use correct graph as reference
    refPos = 0
    for i, g in enumerate(gList, 0):
        if g.getName() == opts.refHisto:
            refPos = i
            break

    # Reference histograph
    gList.insert(0, gList.pop(refPos) )
    gListR.insert(0, gListR.pop(refPos) )
    
    # Create comparison plot
    PlotTFsCompare("transferFactors" , sKeys, gList)

    # Create comparison ratio plot
    gListR = [divideGraph(g, gListR[0], errorY=False, percentDiff=False, invRatio=False) for g in gListR]
    PlotTFsCompare("transferFactorsR", sKeys, gListR, isRatio=True)

    Print("All plots saved under directory %s" % (ShellStyles.NoteStyle() + aux.convertToURL(opts.saveDir, opts.url) + ShellStyles.NormalStyle()), True)
    return


def PlotTFsCompare(pName, sKeys, gList, isRatio=False):

    # Finally do a all-in=one plot
    plot  = plots.ComparisonManyPlot(gList[0], gList[1:])
    for k in sKeys:
        plot.histoMgr.setHistoLegendLabelMany({
                k : k,
                })

    # For-loop: All graphs
    for i, s in enumerate(sKeys, 1):
        # Reference histo is exception (draw just a line)
        if s == opts.refHisto and isRatio:
            plot.histoMgr.setHistoDrawStyle(s, "L")
            plot.histoMgr.setHistoLegendStyle(s, "L")
        elif s == opts.refHisto and not isRatio:
            plot.histoMgr.setHistoDrawStyle(s, "C")
            plot.histoMgr.setHistoLegendStyle(s, "L")
        else:
            plot.histoMgr.setHistoDrawStyle(s, "P")
            plot.histoMgr.setHistoLegendStyle(s, "LP")

    plot.setLegend(getLegend(opts, dx=0, dy=-0.3) )
    plot.createFrame(pName, saveFormats=[])
    plot.frame.GetXaxis().SetTitle("")
    plot.frame.GetYaxis().SetTitle("transfer factor")
    plot.draw()
    plot.setLuminosity(opts.intLumi)
    plot.addStandardTexts(addLuminosityText=False, cmsTextPosition="outframe")
    SavePlot(plot, pName, os.path.join(opts.saveDir, "") )
    return


def PlotTFs(counter, iName, iModule):
    
    # Define lists (later converted to arrays)
    xval  = []
    xerrl = []
    xerrh = []
    yval  = []
    yerrl = []
    yerrh = []

    # Ensure correct style is applied to refHisto
    sKeys = sorted(iModule.FakeBNormalisation_Value.keys(), key=natural_keys)

    # Fill TGraph arrays
    for i, k in enumerate(sKeys, 1):
        
        bin   = k
        value = iModule.FakeBNormalisation_Value[k]
        yerr  = iModule.FakeBNormalisation_Error[k]
        xerr  = yerr
        if k == "Inclusive":
            bin = len(iModule.FakeBNormalisation_Value.keys())  + 1
            
        xval.append(i) #bin)
        xerrl.append(xerr)
        xerrh.append(xerr)
        Verbose("i = %d, k = %s" % ( i, k), i==1)
        yval.append(value)
        yerrl.append(yerr)
        yerrh.append(yerr)

    # Create TGraph object
    tgraph= ROOT.TGraphAsymmErrors(len(xval),
                                   array.array("d", xval ),
                                   array.array("d", yval ),
                                   array.array("d", xerrl),
                                   array.array("d", xerrh),
                                   array.array("d", yerrl),
                                   array.array("d", yerrh)
                                   )
    # Apply styles
    Verbose("Setting style #%d for name \"%s\" and module \"%s\"" % (counter, iName, os.path.basename(str(iModule))), counter==0)
    setStyle(counter, tgraph, isRefHisto= (iName==opts.refHisto) )

    # Set graph name
    tgraph.SetName(iName)

    # Convert the TGraphs to HistoGraphs and append to a list
    graphs = []
    graphs.extend([
            histograms.HistoGraph(tgraph, iName, drawStyle="P", legendStyle="LP"),
            ])

    # Plot the TGraphs
    plot = plots.PlotBase(graphs, saveFormats = [".png", ".C", ".pdf"])
    plot.setLuminosity(opts.intLumi)

    # Customise legend entries
    plot.histoMgr.setHistoLegendLabelMany({
            iName : iName,
            })
    
    # Create legend
    plot.setLegend(getLegend(opts) )

    # Create a frame to be able to impose custom x- and y- range
    plot.createFrame(iName, saveFormats=[])

    # Add cut box?
    if opts.cutLine > 0:
        kwargs = {"greaterThan": True}
        plot.addCutBoxAndLine(cutValue=opts.cutLine, fillColor=ROOT.kRed, box=False, line=True, **kwargs)

    # Set axes title
    plot.frame.GetXaxis().SetTitle("") #"bin") 
    plot.frame.GetYaxis().SetTitle("transfer factor")

    # Draw the plot with standard texts
    plot.draw()
    plot.addStandardTexts()
    
    # Add text on canvas
    if 0:
        histograms.addText(0.55, 0.84, "fully hadronic final state", size=20)
    
    # Save the plots
    SavePlot(plot, "transferFactors_%s" % (iName), os.path.join(opts.saveDir, "") )

    # Debugging
    if 0:
        for g in gList:
            Verbose("%s , x = %s, y = %s "% (g.getRootHisto().GetName(), g.getRootHisto().GetX()[0], g.getRootHisto().GetY()[0]), False)
    return graphs

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
        saveNameURL = aux.convertToURL(saveNameURL, opts.url)
        Verbose(saveNameURL, i==0)
        plot.saveAs(saveName, formats=saveFormats)
    return

def getLegend(opts, dx=0, dy=0):

    # Create customised legend
    xLeg1 = 0.65 + dx
    xLeg2 = 0.93 
    yLeg1 = 0.82 + dy
    yLeg2 = 0.92

    # Adjust legend slightly to visually align with text
    legend = histograms.createLegend(xLeg1*.98, yLeg1, xLeg2, yLeg2) 
    legend.SetMargin(0.17)

    # Make room for the final state text
    # legend.SetFillStyle(1001) #legend.SetFillStyle(3001)
    return legend

def setNominalStyle(graph):
    graph.SetLineStyle(ROOT.kSolid)
    graph.SetLineWidth(3)
    graph.SetLineColor(ROOT.kRed)
    graph.SetMarkerStyle(ROOT.kFullCircle)
    graph.SetMarkerColor(ROOT.kRed)
    return

def setStyle(i, graph, isRefHisto):
    cList = [ROOT.kRed, ROOT.kAzure, ROOT.kOrange-3, ROOT.kMagenta, ROOT.kGreen-1, ROOT.kViolet, ROOT.kTeal+2, ROOT.kGray+1]
    mList = [ROOT.kFullCircle, ROOT.kFullCircle, ROOT.kFullTriangleUp, ROOT.kFullTriangleDown, ROOT.kFullSquare, ROOT.kFullSquare, ROOT.kFullCross, ROOT.kFullCross]
    if i < len(cList) and i < len(mList) :
        colour = cList[i]
        marker = mList[i]
    else: 
        raise Exception("Exceeded list size!")
    graph.SetLineStyle(ROOT.kSolid)
    graph.SetLineWidth(3)
    graph.SetLineColor(colour)    
    graph.SetMarkerSize(1.2)
    graph.SetMarkerStyle(marker)
    graph.SetMarkerColor(colour)
    if mList[i] == ROOT.kOpenCross or mList[i] == ROOT.kFullCross:
        graph.SetMarkerSize(1.50)
    if mList[i] == ROOT.kFullTriangleUp or mList[i] == ROOT.kFullTriangleUp:
        graph.SetMarkerSize(1.45)

    if isRefHisto:
        Verbose("graph.GetName() = %s" % (graph.GetName()), True)
    return

def setStyle1(graph):
    graph.SetFillColor(ROOT.kGreen-3)
    setExpectedStyle(graph)
    return    

def setStyle2(graph):
    graph.SetFillColor(ROOT.kYellow)
    setExpectedStyle(graph)
    return

if __name__ == "__main__":

    # Default Settings
    ANALYSISNAME = "FakeBMeasurement"
    SEARCHMODE   = "80to1000"
    DATAERA      = "Run2016"
    VERBOSE     = False
    PAPER       = False
    CUTLINE     = 0
    LOGX        = False
    LOGY        = False
    GRIDX       = False
    GRIDY       = False
    MINY        = -1
    MAXY        = -1
    SAVEDIR     = None
    REFHISTO    = "Run2016"
    URL         = False
    OPTMODE     = ""

    parser = OptionParser(usage="Usage: %prog [options]")

    parser.add_option("-v", "--verbose", dest="verbose", default=VERBOSE, action="store_true",
                      help="Verbose mode for debugging purposes [default: %s]" % (VERBOSE))

    parser.add_option("--analysisName", dest="analysisName", type="string", default=ANALYSISNAME,
                      help="Override default analysisName [default: %s]" % ANALYSISNAME)

    parser.add_option("--searchMode", dest="searchMode", type="string", default=SEARCHMODE,
                      help="Override default searchMode [default: %s]" % SEARCHMODE)

    parser.add_option("--dataEra", dest="dataEra", type="string", default=DATAERA, 
                      help="Override default dataEra [default: %s]" % DATAERA)

    parser.add_option("-o", "--optMode", dest="optMode", type="string", default=OPTMODE, 
                      help="The optimization mode when analysis variation is enabled  [default: %s]" % OPTMODE)

    parser.add_option("--logX", dest="logX", default=LOGX, action="store_true",
                      help="Enable x-axis log scale [default: %s]" % (LOGX))

    parser.add_option("--logY", dest="logY", default=LOGY, action="store_true",
                      help="Enable y-axis log scale [default: %s]" % (LOGY))

    parser.add_option("--url", dest="url", action="store_true", default=URL,
                      help="Don't print the actual save path the plots are saved, but print the URL instead [default: %s]" % URL)

    parser.add_option("--cutLine", dest="cutLine", type="int", default=CUTLINE,
                      help="Number of digits (precision) to print/save limit results [default: %s]" % (CUTLINE) )

    parser.add_option("--gridX", dest="gridX", default=GRIDX, action="store_true",
                      help="Enable the grid for the x-axis [default: %s]" % (GRIDX) )

    parser.add_option("--gridY", dest="gridY", default=GRIDY, action="store_true",
                      help="Enable the grid for the y-axis [default: %s]" % (GRIDY) )

    parser.add_option("--yMin", dest="yMin", default=MINY, type="float",
                      help="Overwrite automaticly calculated minimum value of y-axis [default: %s]" % (MINY) )

    parser.add_option("--saveDir", dest="saveDir", type="string", default=SAVEDIR,
                      help="Directory where all plots will be saved [default: %s]" % SAVEDIR)

    parser.add_option("-m", "--mcrab", dest="mcrab", action="store", 
                      help="Path to the multicrab directory for input")

    parser.add_option("--refHisto", dest="refHisto", action="store", default=REFHISTO,
                      help="Name of histogram to be used as refernce in comparison many plotter [default: %s]" % (REFHISTO) )

    (opts, args) = parser.parse_args()

    if opts.saveDir == None:
        opts.saveDir = aux.getSaveDirPath("", prefix="", postfix="Test")


    # Require at least two arguments (script-name, path to multicrab)
    if len(sys.argv) < 2:
        parser.print_help()
        sys.exit(1)

    if opts.mcrab == None:
        Print("Not enough arguments passed to script execution. Printing docstring & EXIT.")
        parser.print_help()
        sys.exit(1)

    main(opts)
    
