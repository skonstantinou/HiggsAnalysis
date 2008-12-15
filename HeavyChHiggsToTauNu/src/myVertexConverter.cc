#include "HiggsAnalysis/HeavyChHiggsToTauNu/interface/MyEventConverter.h"

MyVertex MyEventConverter::myVertexConverter(const Vertex& vertex){

	MyVertex V;
	V.x = vertex.x();
	V.y = vertex.y();
        V.z = vertex.z();

        V.dxx  = vertex.covariance(1,1);
        V.dxy  = vertex.covariance(1,2);
        V.dxz  = vertex.covariance(1,3);
        V.dyy  = vertex.covariance(2,2);
        V.dyz  = vertex.covariance(2,3);
        V.dzz  = vertex.covariance(3,3);

	return V;
}

MyVertex MyEventConverter::myVertexConverter(const TransientVertex& vertex){

        MyVertex V(0,0,0);
	if(vertex.isValid()) {
          V.x = vertex.position().x();
          V.y = vertex.position().y();
          V.z = vertex.position().z();

          V.dxx  = vertex.positionError().matrix()(1,1);
          V.dxy  = vertex.positionError().matrix()(1,2);
          V.dxz  = vertex.positionError().matrix()(1,3);
          V.dyy  = vertex.positionError().matrix()(2,2);
          V.dyz  = vertex.positionError().matrix()(2,3);
          V.dzz  = vertex.positionError().matrix()(3,3);
	}
        return V;
}

