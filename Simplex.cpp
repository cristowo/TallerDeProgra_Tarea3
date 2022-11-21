#include "Simplex.h"
#define EPS 1.0e-6
#define NR_END 1

/*
* Clase Simplex para resolver problemas de optimizacion lineal
*/

/*
Constructor
Parametros: m1: numero de restricciones <= ; m2: numero de restricciones >= ; m3: numero de restricciones =
Return:
*/
Simplex::Simplex(int m1, int m2, int m3){
	// faltan cosas aqui
	this->solved=false;
	
}

/*
Destructor
Parametros:
Return:
*/
Simplex::~Simplex(){

}

/*

Carga la matriz del archivo 
Parametros: String del nombre del archivo
return: Booleano indicando si se cargo correctamente
*/

bool Simplex::loadTxt(string filename){
	string line;
	// neceitamos la libreria de manejo de archivo fstream
	// sstream stream de string
	fstream txt_stream(filename);
	stringstream charStream;
	string number_txt;
	vector<float> *number_float;
	
	if (!txt_stream.is_open()){
		cout<<"Archivo: " << filename << " no encontrado" << endl;
		return false;
	} else {
		cout<<"Archivo encontrado " << endl;
	}
											// notar que getline retorna verdadero cuando logra leer algo
	getline(txt_stream, line); 				// lee caracteres hasta fin de linea
	charStream <<line;
	getline(charStream, number_txt, ' '); 	// idem hasta espacio
	m1=stoi(number_txt); 					// transforma string a int
	getline(charStream, number_txt, ' '); 	// idem hasta espacio
	m2=stoi(number_txt); 					// transforma string a int
	getline(charStream, number_txt, ' '); 	// idem hasta espacio
	m3=stoi(number_txt); 					// transforma string a int

	// lee mientras exista una linea que leer
	while(getline(txt_stream,line)){
		charStream.clear();
		charStream << line;
		number_float=new vector<float>;
		while(getline(charStream, number_txt, ' ')) {
			number_float->push_back(stof(number_txt));		
		}
		a.push_back(*number_float);
	}
	N=a[0].size()-1;	// cantidad de variables
	M=a.size()-1; 		// cantidad de restricciones
	NP= N+1;
	MP=M+2;
	NM1M2 = N+m1+m2;

	// falta chequear que sea arreglo rectangular 
	// ie todas las filas del mismo tamaño
	// m1+m2+m3 == M

	// ultimo detalle agregar fila con ceros
	number_float=new vector<float>;
	for(int i=0;i<=N; i++){
		number_float->insert(number_float->begin(),0);
	}
	a.insert(a.begin(),*number_float);

	txt_stream.close();
    return true;
}

/*
Imprime la matriz
Parametros: 
Return: 
*/
void Simplex::print(){
	cout<<"m1: "<<m1<< " m2:" << m2 << " m3:" << m3<< endl;
	cout<<"N:"<<N<< " M:"<<M<<endl;
	cout<<"NP:"<<NP<< " MP:"<<MP<<endl;
	
	int i=0, j=0;
	for(i=0; i<a.size(); i++){
		for(j=0;j<a[i].size();j++){
			cout<<a[i][j] <<" ";
		}
		cout<<endl;
	}
}

// Falta implementar
/*

Parametros:
Return:
*/
void Simplex::insertConstraint(int b, int var, int type){

}

/*
Clona de un Simplex
Parametros:
Return: Simplex clonado
*/
Simplex* Simplex::clone() {
    Simplex *s1 = new Simplex(m1, m2, m3);
	// hacer la copia
	return s1;
}

/*
Solve
Parametros:
Return:
*/
void Simplex::solve() {
	int i,icase,j; // esto lo cambie izrov e iposv
	//vector<int> izrov, iposv;
	// por el momento no cargamos nada del txt y resolvemos este sistema
	float c[MP][NP]=
		{0.0,1.0,1.0,3.0,-0.5,
		740.0,-1.0,0.0,-2.0,0.0,
		0.0,0.0,-2.0,0.0,7.0,
		0.5,0.0,-1.0,1.0,-2.0,
		9.0,-1.0,-1.0,-1.0,-1.0,
		0.0,0.0,0.0,0.0,0.0};

	string txt[NM1M2+1]={" ","x1","x2","x3","x4","y1","y2","y3"};
	
	simplx(M,N,m1,m2,m3, &icase);

	vector<int> izrov(M+1), iposv(M+1);

	// dejar todo esto en la funcion print y cambiar printf por cout << ... 
	if (icase == 1)
		cout << "\nunbounded objective function" << endl;
	else if (icase == -1)
		cout << "\nno solutions satisfy constraints given" << endl;
	else {
		
		for (i=1;i<=N;i++){
			if (izrov[i] <= NM1M2){
				cout << txt[izrov[i]];
			}
		}
		cout <<"\n";
		for (i=1;i<=M+1;i++) {
			if (i == 1 || iposv[i-1] <= NM1M2) {
				if (i > 1)
					cout << txt[iposv[i-1]];
				else
					cout <<"  ";
				cout << "%10.10f" << a[i][1];
				for (j=2;j<=N+1;j++)
					if (izrov[j-1] <= NM1M2)
						cout << "%10.2f" << a[i][j];
				cout <<"\n";
			}
		}
		
	}
	// deben hacer el destructor

	//free_convert_matrix(a,1,MP,1,NP);
	//free_ivector(iposv,1,M);
	//free_ivector(izrov,1,N);
	
}


/*
Se entrega una matriz, calcula y entrega solucion
Parametros: float **a, int M, int N, int m1, int m2, int m3, int *icase, vector<int> izrov, vector<int> iposv
Return:
*/
void Simplex::simplx(int m, int n, int m1, int m2, int m3, int *icase) {
	int i, ip, is, k, kh, kp, nl1;
	float q1, bmax;
	
	if (m != (m1 + m2 + m3)){
		cout <<"Bad input constraint counts in simplx" << endl;
		return;
	}
	vector<int> l1;
	vector<int> l3;

	nl1 = n; // ?? varuavkes
	

	for (k = 0; k < n; k++){l1.insert(l1.begin()+k, k);}
	for (i = 0; i < m; i++){
		cout << a[i+1][1] << endl;
		if (a[i + 1][1] < 0.0){return;}
		iposv.insert(iposv.begin()+i, n + i);
	}
	if (m2 + m3){
		for (i = 0; i < m2; i++){l3.insert(l3.begin()+i, 1);}
		for (k = 0; k < (n + 1); k++){
			q1 = 0.0;
			for (i = m1 ; i < m; i++)
				q1 += a[i + 1][k];
			a[m + 1][k] = -q1;
		}
		for (;;){
			simp1(m + 1, l1, nl1, 0, &kp, &bmax);
			if (bmax <= EPS && a[m + 2][1] < -EPS){*icase = -1;return;}
			else if (bmax <= EPS && a[m + 2][1] <= EPS){
				for (ip = m1 + m2 + 1; ip < m; ip++){
					if (iposv[ip] == (ip + n)){
						simp1(ip, l1, nl1, 1, &kp, &bmax);
						if (bmax > EPS){goto one;}
					}
				}
				for (i = m1; i < m1 + m2; i++)
					if (l3[i - m1] == 1)
						for (k = 0; k < n + 1; k++)
							a[i + 1][k] = -a[i + 1][k];
				break;
			}
			simp2(m, n, &ip, kp);
			if (ip == -1){return;}
		one:
			simp3(m + 1, n, ip, kp);
			if (iposv[ip] >= (n + m1 + m2 + 1)){
				for (k = 0; k < nl1; k++)
					if (l1[k] == kp)
						break;
				--nl1;
				for (is = k; is < nl1; is++)
					l1[is] = l1[is + 1];
			}else{
				kh = iposv[ip] - m1 - n;
				if (kh >= 1 && l3[kh]){
					l3[kh] = 0;
					++a[m + 2][kp + 1];
					for (i = 0; i < m + 2; i++){
						a[i][kp + 1] = -a[i][kp + 1];
					}
				}
			}
			is = izrov[kp];
			izrov[kp] = iposv[ip];
			iposv[ip] = is;
		}
	}
	
	for (;;){
		simp1(0, l1, nl1, 0, &kp, &bmax);
		if (bmax <= EPS){
			*icase = 0;
			//FREEALL return;
			return;
		}
		simp2(m, n, &ip, kp);
		if (ip ==-10){
			return; // icase -1
		}
		simp3(m, n, ip, kp);
		is = izrov[kp];
		izrov[kp] = iposv[ip];
		iposv[ip] = is;
	}
}

/*

Parametros: 
Return: 
*/
void Simplex::simp1(int mm, vector<int> ll, int nll, int iabf, int *kp, float *bmax){
	int k;
	float test;

	if (nll <= 0)
		*bmax=0.0;
	else{
		*kp=ll[1];
		*bmax=a[mm+1][*kp+1];
		for (k=1;k<nll;k++) {
			if (iabf == 0)
				test=a[mm][ll[k]+1]-(*bmax);
			else
				test= abs(a[mm][ll[k]+1]) - abs(*bmax);
			if (test > 0.0) {
				*bmax=a[mm][ll[k]+1];
				*kp=ll[k];
			}
		}
	}
}

/*

Parametros:
Return:
*/
void Simplex::simp2(int m, int n, int *ip, int kp){
	int k,i;
	float qp,q0,q,q1;

	*ip=-1;
	for (i=0;i<m;i++){
		if (a[i+1][kp+1] < -EPS){
 			break;
		}
	}
	if (i>m) return;

	q1 = -a[i+1][0]/a[i+1][kp];

	*ip=i;

	for (i = *ip + 1 ; i<m ; i++) {
		if (a[i+1][kp+1] < -EPS) {
			q = -a[i+1][0]/a[i+1][kp];
			if (q < q1) {
				*ip=i;
				q1=q;
			} else if (q == q1) {
				for (k=0;k<n;k++) {
					qp = -a[*ip+1][k+1]/a[*ip+1][kp];
					q0 = -a[i+1][k+1]/a[i+1][kp];
					if (q0 != qp) break;
				}
				if (q0 < qp) *ip=i;
			}
		}
	}
}

/*

Parametros:
Return:
*/
void Simplex::simp3(int i1, int k1, int ip, int kp){
	int kk,ii;
	float piv;

	piv=1.0/a[ip+1][kp+1];

	for (ii=0; ii < i1+1 ;ii++){
		if (ii-1 != ip) {

			a[ii][kp+1] *= piv;
			for (kk=0;kk<=k1+1;kk++)
				if (kk-1 != kp)
					a[ii][kk] -= a[ip+1][kk]*a[ii][kp+1];

		}
	}
	for (kk=0;kk<k1+1;kk++)
		if (kk-1 != kp){
			 a[ip+1][kk] *= -piv;
		}
	a[ip+1][kp+1]=piv;
}



