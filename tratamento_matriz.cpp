#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;
using Matriz = vector<vector<float>>;

Matriz abrir_matriz(string nome);
bool imprimir(Matriz matriz);
bool transpor(Matriz matriz);
bool negativar(Matriz &matriz);
bool mult_escalar(Matriz &matriz, float esc);
Matriz somar(Matriz m1, Matriz m2);
Matriz multi(Matriz m1, Matriz m2);
float determinante(Matriz m1);

int main(){
	Matriz m1  = abrir_matriz("matriz.txt");
	Matriz m2 = abrir_matriz("matriz2.txt");
	
	imprimir(m1);
	//imprimir(m2);
	/*Matriz m3 = multi(m1,m2);
	if(!m3.empty()){
		imprimir(m3);
	}else{
		cout<<"falhou";
	}*/
	float det = determinante(m1);
	cout<<det<<endl;
}

Matriz abrir_matriz(string nome){
	ifstream arq(nome);
	
	if(!arq){
		cerr<<"Erro ao abrir arquivo\n";
		return {};
	}
	int lin,col;
	arq>>lin>>col;
	Matriz matriz(lin,vector<float>(col));
	/*for(int i=0;i<lin;i++){
		matriz[i].resize(col);
	}*/
	for(int i=0;i<lin;i++){
		for(int j=0;j<col;j++){
			arq>>matriz[i][j];
		}
	}
	
	return matriz;
}

bool imprimir(Matriz matriz){
	for(vector<float> v : matriz){
		for(float n : v){
			cout<<n<<"\t";
		}
		cout<<endl;
	}
	cout<<endl;
}

bool transpor(Matriz matriz){
	for(int i=0;i<matriz.size();i++){
		for(int j=0;j<matriz[i].size();j++){
			cout<<matriz[j][i]<<"\t";
		}
		cout<<endl;
	}
	cout<<endl;
	return true;
}

bool negativar(Matriz &matriz){
	for(int i=0;i<matriz.size();i++){
		for(int j=0;j<matriz[i].size();j++){
			matriz[i][j] = matriz[i][j]*(-1);
		}
	}
	return true;
}

bool mult_escalar(Matriz &matriz, float esc){
	for(int i=0;i<matriz.size();i++){
		for(int j=0;j<matriz[i].size();j++){
			matriz[i][j] = matriz[i][j]*(esc);
		}
	}
	return true;
}

Matriz somar(Matriz m1, Matriz m2){
	if(m1.size()!=m2.size() || m1[0].size()!=m2[0].size()){
		return {};
	}
	Matriz m3(m1.size(),vector<float>(m1[0].size()));
	
	for(int i=0;i<m1.size();i++){
		for(int j=0;j<m1[i].size();j++){
			m3[i][j]=m1[i][j]+m2[i][j];
		}
	}
	
	return m3;
}

Matriz multi(Matriz m1, Matriz m2){
	if(m1[0].size()!=m2.size()){
		return {};
	}
	
	Matriz m3(m1.size(),vector<float>(m2[0].size(),0.0f));
	
	for(int i=0;i<m1.size();i++){
		for(int j=0;j<m2[0].size();j++){
			for(int k=0;k<m1[0].size();k++){
				m3[i][j]+=m1[i][k]*m2[k][j];
			}
		}
	}
	
	return m3;
}

float determinante(Matriz m1){
	float det=1,coef=0;
	
	if(m1.size()!=m1[0].size()){
		cerr<<"falha determinante";
		return 0;
	}
	
	vector<float> pivo(m1.size(),0);
	
	for(int i=0;i<m1.size()-1;i++){
		for(int j=0;j<m1[i].size();j++){
			pivo[j]=m1[i][j];
		}
		
		for(int j=i+1;j<m1.size();j++){
			coef=m1[j][i]/pivo[i];
			//tem q subtrair a linha pivo na linha j
			for(int k=0;k<m1.size();k++){
				m1[j][k]-=(coef*pivo[k]);
			}
		}
	}
	for(int i=0;i<m1.size();i++){
		det*=m1[i][i];
	}
	return det;
}
