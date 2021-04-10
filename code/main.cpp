#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Ponto.h"

using namespace std;


bool* polos()
{
     //system("tools\\qvoronoi.exe\ FN < tools\\points3d.txt > tools\\regiao.txt");  //vou tirar essas duas linhas para deixar somente a opção "o"
     //system("tools\\qvoronoi.exe\ p < tools\\points3d.txt > tools\\verticesVoronoi.txt");
     system("tools\\qconvex.exe\ Fx  < tools\\points3d.txt > tools\\convexHull.txt");
     
     system("tools\\qvoronoi.exe\ o < tools\\points3d.txt > tools\\vvoff.off");
     system("tools\\qvoronoi.exe\ Fv < tools\\points3d.txt > tools\\testev.txt");
     //system("tools\\qvoronoi.exe\ f < tools\\points3d.txt > tools\\testev.txt");
     
    //system("tools\\hull\\hull.exe\ -f off -oN -ov -i tools\\points.off -oF tools\\regiao.off");

//Arquivos
     //fstream verticesVoronoi;
     fstream amostragem;
     //fstream regiao;
     fstream amostraComPolos;
     fstream convexHull;
     fstream vvoff;

//Abrindo os Arquivos
     //verticesVoronoi.open ("tools\\verticesVoronoi.txt");
     vvoff.open ("tools\\vvoff.off");
     amostragem.open ("tools\\points3d.txt");
     //regiao.open ("tools\\regiao.txt", ios::in);
     amostraComPolos.open ("tools\\amostras_polos.txt");
     convexHull.open ("tools\\convexHull.txt");
     
//Setando o arquivo com a tag 

     amostraComPolos << "3" << "\n";    

//Ler Todos os Vertices de Voronoi
      string lixo;
      int n_triangulo;
      int n_pontos_vv;
      double coor_x1;
      double coor_y1;
      double coor_z1;
      
      vvoff >> lixo;
      cout << lixo << endl;
      vvoff >> n_pontos_vv;
      vvoff >> n_triangulo;
      vvoff >> lixo;
      cout << n_pontos_vv << " " << n_triangulo << " " << lixo << endl;
            
      Ponto *novo_vertice_Voronoi[n_pontos_vv];
      
      int k = 0;
      for(k = 0; k < n_pontos_vv; k++){
      
            vvoff >> coor_x1;
            vvoff >> coor_y1;
            vvoff >> coor_z1;          
            novo_vertice_Voronoi[k] = new Ponto(coor_x1,coor_y1,coor_z1);
      }
/*
//Ler Todos os Vertices de Voronoi
      int dimensao;
      int n_pontos_VerticeV;
      //double coor_x1;
      //double coor_y1;
      //double coor_z1;
      verticesVoronoi >> dimensao;
      verticesVoronoi >> n_pontos_VerticeV;
      
      Ponto *vertice_Voronoi[n_pontos_VerticeV];
      
      //int k = 0;
      for(k = 0; k < n_pontos_VerticeV; k++){
      
            verticesVoronoi >> coor_x1;
            verticesVoronoi >> coor_y1;
            verticesVoronoi >> coor_z1;          
            vertice_Voronoi[k] = new Ponto(coor_x1,coor_y1,coor_z1);
      }
*/     
//Ler amostra

      int dimen_;
      int n_pontos_Amostral;
      double coor_x;
      double coor_y;
      double coor_z;
      
      Ponto* amostra;
      
      amostragem >> dimen_;
      amostragem >> n_pontos_Amostral;
      //amostragem >> coor_x;
      //amostragem >> coor_y;
      //amostragem >> coor_z;
      
      //amostra = new Ponto(coor_x, coor_y, coor_z);
      
      Ponto* amostras[n_pontos_Amostral];
      
      int count = 0;
      for(count = 0; count < n_pontos_Amostral; count++){
      
            amostragem >> coor_x;
            amostragem >> coor_y;
            amostragem >> coor_z;          
            amostras[count] = new Ponto(coor_x,coor_y,coor_z);
            //cout << amostras[count]->coord_x << " " << amostras[count]->coord_y << " " << amostras[count]->coord_z << endl;
      }
      
//Ler convexHull

      int index_vet_hull;
      int num_vet_hull;

      
      convexHull >> num_vet_hull;

      bool EhconvexHull[n_pontos_Amostral];
      for(count = 0; count < n_pontos_Amostral; count++){
      
          EhconvexHull[count] = false;
      }
      count = 0;
      for(count = 0; count < num_vet_hull; count++){
                
          convexHull >> index_vet_hull;
          EhconvexHull[index_vet_hull] = true;
      }
      //cout << EhconvexHull[3] << " " << EhconvexHull[4] <<endl;
      
//Fazendo para todos pontos amostrais a computação dos polos
      
      
      int n_regioes = n_triangulo;
      //regiao >> n_regioes; //modificar para n_triangulo (já modifiquei)
      amostraComPolos << (n_regioes*3 - num_vet_hull) << "\n"; //modificar (já modifiquei)
      
       cout << n_regioes*3 << " - " << num_vet_hull <<endl;
      
      bool Eh_amostra[n_regioes*3]; //modificação (já modifiquei)
      int indice_amostra = 0;
      //for(;;){}
      
      //cout << "Numero de Regiao: " << n_regioes <<endl;

      int cou = 0;
      //for para varrer todos as amostras
      for(cou = 0; cou < n_regioes; cou++){
      
      cout << cou << endl;      
//achar os vertices para a (i)cou-amostra
           
           //amostra em ação!
           
           Ponto* amostra_atual = amostras[cou];
           //cout << "" <<endl;
           //cout << cou <<endl;
           //cout << amostra_atual->coord_x << " " << amostra_atual->coord_y << " " << amostra_atual->coord_z << endl;
           
           int n_verticesVoronoi; // numero de vértices para essa amostra
           vvoff >> n_verticesVoronoi;
                 
           int index_Vertices [n_verticesVoronoi + 1]; //vetor com os indices do vertices para cada amostra (com idice 0 o num de v.v.)
           index_Vertices [0] = n_verticesVoronoi; // numero de vertices de voronoi dessa (cou) amostra
      
           int ind = 0;   //for para ler quais são os vertices de v. para essa amostra
               
           for(ind = 0; ind < index_Vertices [0]; ind++){
            
                int temp;
                vvoff >> temp;
                if(temp >= 0){
                        
                      index_Vertices[ind + 1] = temp;
                      
                }else{
                      index_Vertices[0]--;
                      ind--;
                      //cout << "Entrou" << endl;
                }
           }
            
//encontrando os polos : primeiro construindo o array ordenado

            double distancia = 0;
            int j_index = 0;
            Ponto* polo_temp;
          
            int size_index = 0;
            int ordemVertices[index_Vertices[0]];  //array com os indices ordenados pela distancia
            
            
            //está com erros na hora de criar o array ordenado "Conferir se está com erros mesmo (26/05)"
            for(j_index = 0; j_index < index_Vertices [0]; j_index++){
            
                int index = index_Vertices[j_index + 1];
                //cout << j_index <<endl;
                //cout << index <<endl; 

                if(index >= 0){
                     
                     polo_temp = novo_vertice_Voronoi[index];
                }else{
                      
                     index= (-1)*index;
                     
                     //talvés essa informação seja importante
                     polo_temp = novo_vertice_Voronoi[index];
                }
            
                if(size_index == 0){ // inserindo primeiro elemento

                     ordemVertices[0] = index;
                     size_index = 1; 
                     //cout << index <<endl;
                     
                }else{
                  
                     distancia = amostra_atual->distancia(polo_temp);
                     
                     
                     int count1 = 0;
                     
                     //cout << index <<endl;
                    // cout << distancia <<endl;
                     
                     bool para = false;
                     while(!para){
                         
                         if(count1 == size_index){
                              
                              ordemVertices[count1] = index;
                              size_index++;
                              para = true;
                              
                         }else if(distancia > amostra_atual->distancia(novo_vertice_Voronoi[ordemVertices[count1]])){
                               
                               int in = size_index;
                               for(in = size_index; in > count1; in--){
                                      
                                      ordemVertices[in] = ordemVertices[in-1];       
                               }
                               
                               ordemVertices[count1] = index;
                               size_index++;
                               para = true;
                                     
                         }else{
                               count1++;
                         }
                     }
                }
            }
            
            //local que deve mudar usa forma de escolha (26/05)
            // Primeiro polo, polo+
            Ponto* polo_mais1 = novo_vertice_Voronoi[ordemVertices[0]];
            Ponto* vetor_n1;
            vetor_n1 = polo_mais1->subtracao(amostra_atual);
            
            //procurando o pólo menos
            bool parou1 = false;
            int itin = 1;
            Ponto* polo_menos1;
      
            while(!parou1){
                 polo_menos1 = novo_vertice_Voronoi[ordemVertices[itin]];
                 Ponto* vetor_menos = polo_menos1->subtracao(amostra_atual);
                 double produto = vetor_menos->produtoEscalar(vetor_n1);
                 
                 if(produto < 0){
                      
                      parou1 = true;
                 }else{
                       
                      itin++;
                      if(itin == index_Vertices[0]){
                             parou1 = true;
                      }
                 }
            }
            
            //cout << amostra_atual->coord_x << " " << amostra_atual->coord_y << " " << amostra_atual->coord_z << endl;
            //cout << polo_mais1->coord_x << " " << polo_mais1->coord_y << " " << polo_mais1->coord_z << endl;
            //cout << polo_menos1->coord_x << " " << polo_menos1->coord_y << " " << polo_menos1->coord_z << endl;
            
            //So está descartando o p+ no caso v. está no convex hull  
            
            if (EhconvexHull[cou]){
                
                Eh_amostra[indice_amostra] = true;
                Eh_amostra[indice_amostra + 1] = false;
                indice_amostra = indice_amostra + 2;
                amostraComPolos << amostra_atual->coord_x << " " << amostra_atual->coord_y << " " << amostra_atual->coord_z << "\n";
                amostraComPolos << polo_menos1->coord_x << " " << polo_menos1->coord_y << " " << polo_menos1->coord_z << "\n";
                cout << "OK" << endl;
                //cout << amostra_atual->coord_x << " " << amostra_atual->coord_y << " " << amostra_atual->coord_z << endl;
                //cout << polo_menos1->coord_x << " " << polo_menos1->coord_y << " " << polo_menos1->coord_z << endl;

            }else{
                Eh_amostra[indice_amostra] = true;
                Eh_amostra[indice_amostra + 1] = false;
                Eh_amostra[indice_amostra + 2] = false;
                indice_amostra = indice_amostra + 3;
                amostraComPolos << amostra_atual->coord_x << " " << amostra_atual->coord_y << " " << amostra_atual->coord_z << "\n";
                amostraComPolos << polo_mais1->coord_x << " " << polo_mais1->coord_y << " " << polo_mais1->coord_z << "\n";
                amostraComPolos << polo_menos1->coord_x << " " << polo_menos1->coord_y << " " << polo_menos1->coord_z << "\n";
                cout << polo_menos1->coord_x << " " << polo_menos1->coord_y << " " << polo_menos1->coord_z << endl;

            }
                 
      }
      amostraComPolos.close();
      amostragem.close();
      //regiao.close();
      //verticesVoronoi.close();
      convexHull.close();
      vvoff.close();
      
      return Eh_amostra;
      
}

//retorna o numero de triangulos após o filtro de amostras
int triangulacao(bool eh_amostras[]){
     
     system("tools\\qdelaunay.exe\ Fv < tools\\amostras_polos.txt > tools\\tetraedros.txt");
     
//Arquivos
     fstream tetraedros;
     fstream triangulos;
     fstream amostraComPolos;
     
//Abrindo os Arquivos
     tetraedros.open ("tools\\tetraedros.txt");
     triangulos.open ("tools\\triangulos.txt");
     amostraComPolos.open ("tools\\amostras_polos.txt");
     
//Filtro que deixa passar somente os triangulos amostrais

      int n_tetraedros;
      int index;
      
      tetraedros >> n_tetraedros;
      triangulos << n_tetraedros << "\n";
      //cout << n_tetraedros << endl;
      
      int count = 0;
      int numeroTriangulos = 0;
      
      for(count = 0; count < n_tetraedros; count++){
            //cout << "count: " << count << endl;  
      
            tetraedros >> index;
            
            //cout << "n_pontos: " << index << endl;
            
            int temp[index];
            int j = 0;
            int i = 0;
            int numero = index;
            
            for(i = 0; i < numero; i++){
                  //cout << "i: " << i << endl;
                  
                  tetraedros >> index;
                  //cout << "index: " << index << endl;

                  if(eh_amostras[index]){   //modificação (ja modifiquei)
                      
                      temp[j] = index;
                      j++;
                      //cout << "j: " << j << endl;
                  }
            }
            
            triangulos << j << " ";
            
            //cout << "index: " << j << endl;
            if(j > 2){
                     numeroTriangulos++;
                     //cout << "Ok: " << numeroTriangulos << endl;         
            }

            for(i=0; i < j; i++){
                
                triangulos << temp[i] << " ";
                //cout << "p_t: " << temp[i] << endl;
            }
            
            triangulos << "\n";
      }
      
      
      amostraComPolos.close();
      triangulos.close();
      tetraedros.close();
      return numeroTriangulos;
}



void criarPLY(int numTriangulos, bool eh_amostras[]){
     
//Arquivos
     fstream aresta;
     fstream pontos;
     fstream arquivoPLY;
     fstream amostragem;
     
//Abrindo os Arquivos
     aresta.open ("tools\\triangulos.txt");
     pontos.open ("tools\\amostras_polos.txt");
     arquivoPLY.open ("tools\\arquivoVisualisacao.ply");
     amostragem.open ("tools\\points3d.txt");

//Numero de vertices no Amostras_Polos
     int num_vertices_Amostras_polos;
     int dimensao;
     pontos >> dimensao;
     pontos >> num_vertices_Amostras_polos;
     
     cout << eh_amostras[0] << " " << eh_amostras[1] <<endl;

//Numero de pontos amostrais
     int num_vertices;
     int dimensao_;
     amostragem >> dimensao_;
     amostragem >> num_vertices;
     
//Numero de faces
     int num_faces;
     aresta >> num_faces;

//Cabeçalho
     arquivoPLY << "ply" << "\n";
     arquivoPLY << "format ascii 1.0" << "\n";
     arquivoPLY << "element vertex " << num_vertices << "\n";
     arquivoPLY << "property float x" << "\n" << "property float y" << "\n" << "property float z" << "\n";
     arquivoPLY << "element face " << numTriangulos << "\n";
     arquivoPLY << "property list uchar int vertex_indices" << "\n";
     //arquivoPLY << "property list uchar float texcoord" << "\n";
     //arquivoPLY << "property uchar red" << "\n";
     //arquivoPLY << "property uchar green" << "\n";
     //arquivoPLY << "property uchar blue" << "\n";
     arquivoPLY << "end_header" << "\n";

//Escrita da coordenadas das amostras

     int count =  num_vertices_Amostras_polos; // vai mudar (ja modifiquei)
     double coor_x, coor_y, coor_z;
     int i;
     int novo_indice = 0;
     int novos_indices[count];
     
     
     for(i = 0; i < count; i++){
           pontos >> coor_x;
           pontos >> coor_y;
           pontos >> coor_z;
           
           if(eh_amostras[i]){
                  novos_indices[i] = novo_indice;
                  novo_indice++;
                  arquivoPLY << coor_x << " " << coor_y << " " << coor_z << "\n";
           }
     }

//Escrita das arestas
     
     int i_ponto;
     
     cout << num_faces << endl;
     
     for(i=0;i < num_faces; i++){
           int coun_i;    
           aresta >> coun_i;
           
           if(coun_i < 3){
                     
                int j;
                for(j = 0; j < coun_i; j++){
                 
                      cout << "Ok2!" << coun_i << endl;
                      aresta >> i_ponto;
                }
           }else{
                 arquivoPLY << coun_i << " ";
                 int j;
                 for(j = 0; j < coun_i; j++){
                 
                       //cout << "Ok3!" << coun_i << endl;
                       aresta >> i_ponto;
                       arquivoPLY << novos_indices[i_ponto] << " ";
                 }

                 arquivoPLY << "\n";     
           }
     }
     
     pontos.close();
     aresta.close();
     arquivoPLY.close();
     amostragem.close();
}



int main(int argc, char *argv[])
{
    bool* eh_amostras;
    eh_amostras = polos();
    int num_tringulos = triangulacao(eh_amostras);
    criarPLY(num_tringulos, eh_amostras);
    
    system("PAUSE");
    
    return EXIT_SUCCESS;
}
