#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <climits>
/*
 *STL headers
 */
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>

using namespace std;

struct Point {
  GLint x;
  GLint y;
};
map<int, Point> int_to_Point;

bool compare_func(
    const pair< pair<int,int>, int>& x, 
    const pair< pair<int,int>, int>& y) {

    return x.second < y.second;
}
bool compare_func1(
    const pair<int,int>& x, //For min Heap
    const pair<int,int>& y) {

    return x.second > y.second;
}
// struct map_comp_func {
//   bool operator() (const Point& lhs, const Point& rhs) const
//   {return lhs.x<rhs.x;}
// };
// struct map_comp_func2 {
//   bool operator() (const pair<Point,Point>& lhs, const pair<Point,Point>& rhs) const
//   {return lhs.first.x<rhs.first.x;}
// };

class Graph
{
    public:
    int num_of_edges;
    int num_of_vertices;
    vector<int> nodes;
    map< int,vector<int> > edges;
    //vector< pair< pair<Point,Point>, int >> weights_edges_v;
    map< pair<int,int>, int> weights_edges;


    Graph(){
      num_of_edges = 0;
      num_of_vertices = 0;
    }

    void add_node(int n){
      nodes.push_back(n);
      edges.insert(make_pair(
                      n, 
                      vector<int>()));
      // cout<<"\n"<<n.x<<"-->"<<n.y;
      num_of_vertices++;
    }

    void add_edge(int from_node, int to_node, int weight){

      edges[from_node].push_back(to_node);
      edges[to_node].push_back(from_node);
      cout<<'\n'<<from_node<<"----"<<to_node<<"    "<<weight;
      weights_edges.insert(
          make_pair(
              pair<int,int>(from_node,to_node), 
              weight));
      weights_edges.insert(
          make_pair(
              pair<int,int>(to_node,from_node), 
              weight));
      num_of_edges++;
    }

    vector< pair< int, int >> min_span_tree_kruskal(){
      vector< pair< int, int >> min_tree;
      vector<int> parent(num_of_vertices,-1);

      vector< pair< pair<int,int>, int> > edges;
      for (map< pair<int,int>, int>::iterator i = weights_edges.begin(); 
                                          i != weights_edges.end(); ++i){
        edges.push_back(*i);       
      }
      sort(edges.begin(), edges.end(), compare_func);

      pair< pair<int,int>, int > x;
          
      while(min_tree.size() < num_of_vertices - 1 ) {
          x = edges[0];
          edges.erase(edges.begin());
          if (!check_cycle(parent, x))
          {
            min_tree.push_back(x.first);
          }
      }
      return min_tree;
    }

    bool check_cycle(
      vector<int> &parent,
      pair< pair<int,int>, int > edge){
      
      int x = _find(parent, edge.first.first);
      int y = _find(parent, edge.first.second);

      if (x == y)
        return true;
      //Union Step
      parent[x] = y; 
      // copy(parent.begin(), parent.end(),
      //     ostream_iterator<int>(cout," "));
      // cout<<"\n";
      
      return false;  
    }

    int _find(vector<int> &parent, int p){
      if( parent[p] == -1) {
        return p;
      }
      return _find(parent, parent[p]);
    }



    vector< pair< int, int >> prims_min_tree(){
      vector< pair< int, int >> min_tree;
      vector<int> parent(num_of_vertices,-1);
      vector<int> index(num_of_vertices);

      vector<pair< int, int >> min_heap; //value and key pair
      min_heap.push_back(make_pair(0,0));
      index[0] = 0;
      for(unsigned i = 1; i < num_of_vertices; ++i) {
        min_heap.push_back(make_pair(i,INT_MAX));
        index[i] = i;
      }

      int heap_size = num_of_vertices;
      // make_heap(min_heap.begin(), min_heap.end(), compare_func1);
      int i;
      pair< int, int > temp;
      while(heap_size) {
          i = min_heap[0].first;
          min_heap[0].second = -1;
  
          for (vector<int>::iterator j = edges[i].begin(); j != edges[i].end(); ++j){
            if(min_heap[index[*j]].second > weights_edges[make_pair(i,(*j))]) {
              if(index[*j] < heap_size) { // Checking if it is present in min_Heap
                min_heap[index[*j]].second = weights_edges[make_pair(i,(*j))];
                parent[*j] = i;
                // cout<<'\n'<<*j<<" "<<i;
                int k = index[*j];
                
                while(k>0 && min_heap[k].second < min_heap[(k-1)/2].second) {
                    temp = min_heap[(k-1)/2];
                    min_heap[(k-1)/2] = min_heap[k];
                    min_heap[k] = temp;
                    index[min_heap[k].first] = k;
                    index[min_heap[(k-1)/2].first] = (k-1)/2;
                    k = (k-1)/2;
                }
              }
            }
          }
          // cout<<'\n';
          //  for(unsigned i = 0; i < num_of_vertices; ++i) {
          //     cout<<min_heap[i].first<<"-->"<<min_heap[i].second<<" ";
          //   }
          temp = min_heap[heap_size-1];
          min_heap[heap_size-1] = min_heap[0];
          min_heap[0] = temp;
          index[min_heap[0].first] = 0;
          index[min_heap[heap_size-1].first] = heap_size-1;
          heap_size--;  
          // cout<<'\n';
           // for(unsigned i = 0; i < num_of_vertices; ++i) {
           //    cout<<min_heap[i].first<<" ";
           //  }       
          min_heapify (min_heap, 0, heap_size, index); 
          // cout<<'\n';
           // for(unsigned i = 0; i < num_of_vertices; ++i) {
           //    cout<<min_heap[i].first<<" ";
           //  }
          
          

      }
      for(i = 0; i < num_of_vertices; ++i) {
        if(parent[i] != -1) {
          min_tree.push_back(make_pair(i,parent[i]));
        } 
      }
      return min_tree;

   }

   void min_heapify(std::vector<pair< int, int >> &v, int index, int size, vector<int> &pos){

      int left_child = 2*index + 1;
      int right_child = 2*index +2;
      int heap_size = size;
      int smallest = index;

      if (left_child < heap_size && v[left_child].second < v[index].second)
      {
        smallest = left_child;
      }
      if (right_child < heap_size && v[right_child].second < v[smallest].second)
      {
        smallest = right_child;
      }
      if (smallest != index)
      {
          pair< int, int > temp = v[smallest];
          v[smallest] = v[index];
          v[index] = temp;
          pos[v[index].first] = index;
          pos[v[smallest].first] = smallest;

      min_heapify(v,smallest,size, pos);
  }
}
      
};

Point p1, p2;
Graph G;
int max_edges = 0;

void draw_line(Point p1, Point p2) {
  glColor3f(0.0f, 0.0f, 1.0f);

  GLfloat dx = p2.x - p1.x;
  GLfloat dy = p2.y - p1.y;

  GLfloat x1 = p1.x;
  GLfloat y1 = p1.y;

  GLfloat step = 0;

  if(abs(dx) > abs(dy)) {
    step = abs(dx);
  } else {
    step = abs(dy);
  }

  GLfloat xInc = dx/step;
  GLfloat yInc = dy/step;

  for(float i = 1; i <= step; i++) {
    glVertex2i(x1, y1);
    x1 += xInc;
    y1 += yInc;
  }
  glEnd();
  glFlush();
}

Point transform(Point P){
  int x = P.x;
  int y = P.y;
  Point P2;
  P2.x = 20*((x-1)/20) + 10;
  P2.y = 20*((y-1)/20) + 10;
  return P2;
}

void draw_circle(Point pC, GLfloat radius) {
  glColor3f(1.0f, 0.0f, 0.0f);

  GLfloat step = 1/radius;
  GLfloat x, y;
  
  for(GLfloat theta = 0; theta <= 360; theta += step) {
    x = pC.x + (radius * cos(theta));
    y = pC.y + (radius * sin(theta));
    glVertex2i(x, y);
  }
}

void myMouseFunc(int button, int state, int x, int y)
{
  if (max_edges == G.num_of_edges ){
    
    if(state == GLUT_DOWN){
      return;
    }
    cout<<"\nMax Limit Reached. Now Showing Minimum spanning Tree";
    vector< pair< int, int >> min_tree;
    if(button == GLUT_LEFT_BUTTON) {
      cout<<"\nMinimum spanning Tree: Kruskal's Method";
      min_tree = G.min_span_tree_kruskal();
    }
    else{
      cout<<"\nMinimum spanning Tree: Prim's Method";
        min_tree = G.prims_min_tree();
    }
    
    glClear(GL_COLOR_BUFFER_BIT);    
    //vector< pair< pair<Point,Point>, int >> min_tree = G.min_span_tree_kruskal();
    
    map<int, Point>::iterator itr;
    for(unsigned i = 0; i < min_tree.size(); ++i) {
      glBegin(GL_POINTS);

      itr = int_to_Point.find(min_tree[i].first);
      p1.x = itr->second.x;
      p1.y = itr->second.y;
      itr = int_to_Point.find(min_tree[i].second);
      p2.x = itr->second.x;
      p2.y = itr->second.y;
      draw_circle(p1, 5);
      draw_circle(p2, 5);
      draw_line(p1, p2);
    }
    return;
  }
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    p1.x = x;
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    p1.y = h - y;
    p1 = transform(p1);
    // glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    draw_circle(p1, 5);
    // cout<<x<<" "<<y<<'\n';
  }
  else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
    p2.x = x;
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    p2.y = h - y;
    p2 = transform(p2);
    bool check1 = true, check2 = true;
    int temp1, temp2;
    //cout<<p1.x<<" "<<p1.y<<"  "<<p2.x<<" "<<p2.y<<"\n";
    for (map<int, Point>::iterator i = int_to_Point.begin(); i != int_to_Point.end(); ++i)
    {
      if((*i).second.x == p1.x && (*i).second.y == p1.y) {
        check1 = false;
        temp1 = (*i).first;
        if(!check2) {
          break;
        }
      }
      if((*i).second.x == p2.x && (*i).second.y == p2.y) {
        check2 = false;
        temp2 = (*i).first;
        if(!check1) {
          break;
        }
      }

    }
    if (check1)
    {
      int_to_Point.insert(make_pair(G.num_of_vertices, p1)); 
      temp1 = G.num_of_vertices;
      G.add_node(G.num_of_vertices);

    }
    if (check2 && (p1.x != p2.x || p1.y != p2.y))
    {
      int_to_Point.insert(make_pair(G.num_of_vertices, p2)); 
      temp2 = G.num_of_vertices;
      G.add_node(G.num_of_vertices);
    }
    if(p1.x != p2.x || p1.y != p2.y){
      int weight = sqrt(
                      pow(p1.x - p2.x,2)+ 
                      pow(p1.y - p2.y,2));     
      G.add_edge(temp1, temp2, weight);
    }
    draw_circle(p2, 5);
    draw_line(p1, p2);
    cout<<int_to_Point.size();  
  }
}

void init() {
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glPointSize(5.0f);
  gluOrtho2D(0.0f, 1280.0f, 0.0f, 720.0f);
}
void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glEnd();
  glFlush();
}

int main(int argc, char **argv) {
  cout<<"Enter max number of edges?\n";
  cin>>max_edges;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowPosition(200, 200);
  glutInitWindowSize(1280, 720);
  glutCreateWindow("Make your graph");
  glutDisplayFunc(display);
  glutMouseFunc(myMouseFunc);
  init();
  glutMainLoop();

  return 0;
}