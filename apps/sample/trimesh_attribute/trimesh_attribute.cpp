
#include<vcg/simplex/vertexplus/base.h>
#include<vcg/simplex/vertexplus/component.h>
#include<vcg/simplex/faceplus/base.h>
#include<vcg/simplex/faceplus/component.h>
#include<vcg/complex/trimesh/base.h>
#include<vcg/complex/trimesh/allocate.h>

class MyFace;
class MyVertex;
class MyEdge;   // dummy prototype never used
class MyVertex  : public vcg::VertexSimp2< MyVertex, MyEdge, MyFace, vcg::vertex::Coord3f,vcg::vertex::Normal3f>{};
class MyFace    : public vcg::FaceSimp2< MyVertex, MyEdge, MyFace, vcg::face::VertexRef, vcg::face::Normal3f> {};

class MyMesh : public vcg::tri::TriMesh< std::vector<MyVertex>, std::vector<MyFace> > {};

 
float Irradiance(MyMesh::VertexType v){
	// .....
	return 1.0;
}

int main()
{
  MyMesh m;
  //...here m is filled
  
  // add a per-vertex attribute with type float named "Irradiance"
  MyMesh::PerVertexAttributeHandle<float> ih = vcg::tri::Allocator<MyMesh>::AddPerVertexAttribute<float> (m,std::string("Irradiance"));

  // add a per-vertex attribute with type float named "Radiosity"   
  vcg::tri::Allocator<MyMesh>::AddPerVertexAttribute<float> (m,std::string("Radiosity"));
 
  // add a per-vertex attribute with type bool and no name specified
  MyMesh::PerVertexAttributeHandle<bool> blocked_h = vcg::tri::Allocator<MyMesh>::AddPerVertexAttribute<bool> (m); 
  
  MyMesh::VertexIterator vi; int i = 0;
  for(vi   = m.vert.begin(); vi != m.vert.end(); ++vi,++i){
   ih[vi]  = Irradiance(*vi);  // [] operator takes a iterator
   ih[*vi] = Irradiance(*vi);  // or a MyMesh::VertexType object
   ih[&*vi]= Irradiance(*vi);  // or a pointer to it
   ih[i]   = Irradiance(*vi);  // or an integer index
  }
    
  // Once created with AddPerVertexAttribute, an handle to the attribute can be obtained as follows
  MyMesh::PerVertexAttributeHandle<float> rh = vcg::tri::Allocator<MyMesh>::GetPerVertexAttribute<float>(m,"Radiosity");

  // you can query if an attribute is present or not
  bool hasRadiosity = vcg::tri::HasPerVertexAttribute(m,"Radiosity");

  // you can delete an attibute by name
  vcg::tri::Allocator<MyMesh>::DeletePerVertexAttribute<float>(m,"Radiosity");

  // you can delete an attibute by handle
  vcg::tri::Allocator<MyMesh>::DeletePerVertexAttribute<bool>(m,blocked_h);
}