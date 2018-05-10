#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;
void analizar(string cad);
void archivarFunciones();
void obtenerFunciones();
int lineasAnalizadas = 0;
struct pal{
 string nombre;
 int repe;
};

fstream ar;
ofstream salida;
ofstream fun;

float N1; // numero total de ocurrencias de operadores
float N2; // numero total de ocurrencias de operandos
float n1; // numero de operadores unicos
float n2; // numero de operandos unicos

string cad;

vector<pal*> operadores;
vector<pal*> operandos;
vector<pal*> funciones;
////////////////////////////////////////////////////////////////////////////////

void etiqueta(){
 string c;
 ar>>c;
 while (!ar.eof() && c.compare(">" ) != 0) {
   cout<<"Se analizo "<<c<<endl;
   analizar(c);
   //system("pause");
   if (c.compare("\n") == 0) lineasAnalizadas++;
   ar>>c;  
 }
 
}

////////////////////////////////////////////////////////////////////////////////
bool aritmetico(string cad){
  if (cad.compare("+") ==0 ||
      cad.compare("-") ==0 ||
      cad.compare("/") ==0 ||
      cad.compare("%") ==0 
      )return true;
  
  return false;
}

////////////////////////////////////////////////////////////////////////////////
bool relacional(string cad){
 if (cad.compare("+") ==0 ||
     cad.compare("-") ==0 ||
     cad.compare("/") ==0 ||
     cad.compare("*") ==0 ||
     cad.compare("%") ==0 
     )return true;
  
  return false;
} 


////////////////////////////////////////////////////////////////////////////////
bool logicos(string cad){
     
 if (cad.compare("!") ==0 ||
     cad.compare("&&") ==0 ||
     cad.compare("||") ==0 
     )return true;
  
  return false;
}
////////////////////////////////////////////////////////////////////////////////
bool igualdad(string cad){
  if (cad.compare("==") ==0 ||
      cad.compare("===") ==0 
     )return true;
  
  return false;

}
////////////////////////////////////////////////////////////////////////////////
bool noIgualdad(string cad){
  if (cad.compare("!=") ==0 
     )return true;
     
  return false; 
}

////////////////////////////////////////////////////////////////////////////////
bool incDec(string cad){
 if (cad.compare("++") ==0 ||
     cad.compare("--") ==0
     )return true;
  
  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool asignacion(string cad){
     
  if (cad.compare("=")  == 0 ||
      cad.compare("-=") == 0 ||
      cad.compare("/=") == 0 ||
      cad.compare("*=") == 0 ||
      cad.compare("+=") == 0
     )return true;
  
  return false;
}

////////////////////////////////////////////////////////////////////////////////
bool palabraReservada(string cad){
  if (cad.compare("if")  == 0 ||
      cad.compare("else") == 0 ||
      cad.compare("while") == 0 ||
      cad.compare("for") == 0 ||
      cad.compare("int") == 0 ||
      cad.compare("float") == 0 ||
      cad.compare("double") == 0 ||
      cad.compare("echo") == 0 ||
      cad.compare("function") == 0 ||
      cad.compare("case") == 0 ||
      cad.compare("switch") == 0 ||
      cad.compare("break") == 0 ||
      cad.compare("String") == 0 
     )return true;
  
  return false;
}
////////////////////////////////////////////////////////////////////////////////
bool funcion(){
  string c;
  ar>>c;
  while (!ar.eof() && c.compare(")") != 0) {
    if (c.compare(",") != 0) analizar(c);
    ar>>c;  
  }

}
////////////////////////////////////////////////////////////////////////////////
bool isOperador(string cad){
 string c;
 //cout<<"analizando cadena "<<cad<<endl;
 //cout<<"analizando si es operador "<<endl;
 if (cad[0] == '<') {
  if (cad[1] != '?') {etiqueta();}
  //system("pause");
  return true;
 }
 
 if (cad.compare("(") == 0){
   funcion();
 }
 
 if (aritmetico(cad)) return true;
 if (relacional(cad)) return true;
 if (logicos(cad)) return true;
 if (igualdad(cad)) return true;
 if (noIgualdad(cad)) return true;
 if (incDec(cad)) return true;
 if (asignacion(cad)) return true;
 if (palabraReservada(cad))  return true;
 return false;
}
////////////////////////////////////////////////////////////////////////////////
int posicionFun(string cad){
  for (int i=0;  i < funciones.size(); i++){
   if (funciones[i]->nombre.compare(cad) == 0) return i;
  }
 
 return -1;
}
////////////////////////////////////////////////////////////////////////////////
int posicionOper(string cad){

 for (int i=0;  i < operadores.size(); i++){
   if (operadores[i]->nombre.compare(cad) == 0) return i;
 }
 
 return -1;
}

////////////////////////////////////////////////////////////////////////////////
int posicionOperando(string cad){

 for (int i=0;  i < operandos.size(); i++){
   if (operandos[i]->nombre.compare(cad) == 0) return i;
 }
 
 return -1;
}

////////////////////////////////////////////////////////////////////////////////
void analizar(string cad){
  if (isOperador(cad)){
    int x = posicionOper(cad);
    cout<<cad<<" Se colocara en la posicion "<<x<<endl;
    
    
    if (x != -1){
     operadores[x]->repe++;
    
    }else{
     pal *nueva = new pal();
     nueva->nombre=cad;
     nueva->repe = 1;
     operadores.push_back(nueva);
    }
     
  }else{
    
    if (cad.compare("(") != 0){
      int x = posicionOperando(cad);
      cout<<cad<<" Se colocara en la posicion "<<x<<endl;
    
      if (x != -1){
        operandos[x]->repe++;
      }else{
        pal *nueva = new pal();
        nueva->nombre=cad;
        nueva->repe = 1;
        operandos.push_back(nueva);
      }
    }
  }
  
}

//////////////////////////////////////////////////////////////////////////////
void archivar(){
  salida.open("test.txt");
  N1 =0;
  N2 =0;
  int x=0;
  salida<<"Operadores"<<endl<<endl<<endl;
  
  for (x=0; x< operadores.size(); x++){
     N1 += operadores[x]->repe;   
  }
  n1 = x;
  x=0; 
  
  
  for (x=0; x< operadores.size(); x++){
     salida<<operadores[x]->nombre<<" ";
     salida<<operadores[x]->repe;
     salida<<endl;
    // N1 += operadores[x]->repe;
     
  }
  //n1 = x;
  x=0; 
  
  //system("pause");
  salida<<"total de operadores "<<n1<<endl;
  //system("pause");
  
  cout<<"observando operandos almacenados "<<endl;
  for (x=0; x< operandos.size(); x++){
     cout<<operandos[x]->nombre<<" ";
     cout<<operandos[x]->repe;
     cout<<endl;
       
  }
  
  
  
  
  
  
  x=0;
  salida<<endl<<endl<<endl<<"Operandos"<<endl<<endl<<endl;
  for (x=0; x< operandos.size(); x++){
     salida<<operandos[x]->nombre<<" ";
     salida<<operandos[x]->repe;
     salida<<endl;
     N2 += operandos[x]->repe; 
     //cout<<"guardo "<<operandos[x]->nombre<<endl;
     //system("pause");
  }
  n2 = x;
  //system("pause");
  
  salida<<"total de operandos "<<n2<<endl;
  
  
  //system("pause");
  salida<<endl<<endl<<"Resumen de los cálculos "<<endl;
  float N = N1+N2;
  float n = n1+ n2;
  salida<<"Longitud de tokens N = "<<N<<endl;
  salida<<"Vocabulario n = "<<n<<endl;
  float V = (N * log2(n));
  salida<<"Volumen V = "<<V<<endl;
  float L = (2/n1) * (n2/N2);
  salida<<"Nivel de programa L = "<<L<<endl;
  salida<<"Dificultad D = "<<((float) 1 /L)<<endl;
  salida<<"Esfuerzo E = "<<(V/L)<<endl;
  salida<<"Lineas analizadas "<<endl;
  
  /*
  obtenerFunciones();
  archivarFunciones();
  */
  salida.close();

}
////////////////////////////////////////////////////////////////////////////////
void obtenerFunciones(){
     
 fstream f;
 f.open("fun.txt");
 string nombre;
 int can;
 
 while (!f.eof()){
   f>>nombre>>can;
   int x = posicionFun(cad);
     
    
      if (x != -1){
        funciones[x]->repe += can;
      }else{
        pal *nueva = new pal();
        nueva->nombre = nombre;
        nueva->repe = can;
        funciones.push_back(nueva);
      }
 }
 f.close();
}
 
///////////////////////////////////////////////////////////////////////////////
void archivarFunciones(){
  fun.open("fun.txt");

  for (int x=0; x< funciones.size(); x++){
     fun<<funciones[x]->nombre<<" ";
     fun<<funciones[x]->repe;
     fun<<endl;
     
  }
  fun.close();
}
///////////////////////////////////////////////////////////////////////////// 
int main(){
 ar.open("codigo.txt");
 
 while (!ar.eof()){
  
   ar>>cad;
   if (cad.compare("\n") != 0 && cad.compare("{") != 0 && cad.compare("}") != 0) {
    analizar(cad);
    cout<<"se analizo "<<cad<<endl;
    //system("pause");
   }else{
    cout<<"se encontro un salto de linea "<<endl;
     lineasAnalizadas++;
   }
 }
 cout<<"operaciones terminadas "<<endl;
// system("pause");
 ar.close();
 archivar();
 
 return 0;
}
