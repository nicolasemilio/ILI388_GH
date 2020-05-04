#ifndef externo
int Nvariables;
int Precision;
float V;
#endif

#ifdef externo
extern int Nvariables;
extern int Precision;
extern float V;
#endif

struct rango{
  float minimo, maximo;
};

class individuo
{
  friend ostream &operator<<(ostream &, const individuo &);

  public:
    float aptitud;
    bool usado;
    vector <int> cromosoma;
    vector <int> cromosoma_binario;
    vector <float> cromosoma_real;
    
    
      individuo();
  individuo(const individuo &);
  ~individuo(){};
  individuo &operator=(const individuo &rhs);
  int operator==(const individuo &rhs) const;
  int operator<(const individuo &rhs) const;
  
};
    
individuo::individuo()   // Constructor
  {
    aptitud = AMAX;
    usado = true;
    cromosoma=vector<int>(Nvariables*Precision, -1);
    cromosoma_binario=vector<int>(Nvariables*Precision, -1);
    cromosoma_real=vector<float>(Nvariables*Precision, -1.0);
  }
  
individuo::individuo(const individuo &a)
  {
    aptitud = a.aptitud;
    usado = a.usado;
    cromosoma = a.cromosoma;
    cromosoma_real = a.cromosoma_real;
}


ostream &operator<<(ostream &output, const individuo &a)
{
  //output << "[" << &a << "]";
  output << "Q: " << a.aptitud << " # ";

  //output << "Q: " << a.aptitud << "]";
  //output << "[" << a.usado << "]";
  /*for(int i=0; i<a.cromosoma.size(); i++)
    output << a.cromosoma[i] <<" ";
  output<<endl;*/
  /*for(int i=0; i<a.cromosoma_binario.size(); i++)
    output << a.cromosoma_binario[i] <<" ";
  output<<endl;*/
  for(int i=0; i < a.cromosoma_real.size(); i++)
    output << a.cromosoma_real[i] <<" ";
  output<<endl;
  return output;
}

individuo& individuo::operator=(const individuo &a)
{
  this->aptitud = a.aptitud;
  this->usado = a.usado;
  this->cromosoma = a.cromosoma;
  this->cromosoma_binario = a.cromosoma_binario;
  this->cromosoma_real = a.cromosoma_real;

  /*for(int i=0; i<Tinstancia; i++)
  {
    this->cromosoma[i] =  a.cromosoma[i];
  }*/
  return *this;
}

int individuo::operator==(const individuo &a) const
{
  //Ojo!, dos anticuerpos son iguales si tienen la misma aptitud
  if( this->aptitud != a.aptitud) return 0;
  return 1;
}

int individuo::operator<(const individuo &a) const
{
  if( this->aptitud < a.aptitud ) return 1; //REVISAR
  return 0;
}


class conjunto
{
  friend ostream &operator<<(ostream &, conjunto &);

 public:
  char name[TAM];
  vector <individuo> conj;
  conjunto(char n[TAM]);   // Constructor
  ~conjunto();
  void vaciar();
};

conjunto::conjunto(char n[TAM])   // Constructor
  {
    strncpy(name, n, TAM);
  }

 conjunto::~conjunto(void)
  {
    int size = conj.size();
    for(int i=0; i<size; i++)
    {
      conj[i].cromosoma.clear();
    }
    conj.clear();
  }


void conjunto::vaciar(void)
  {
    int size = conj.size();
    for(int i=0; i<size; i++)
    {
      conj[i].cromosoma.clear();
    }
    conj.clear();
  }

ostream &operator<<(ostream &output, conjunto & c )
{
  vector<individuo>::iterator i;
  output<<c.name<<endl;
  output<<c.conj.size()<<endl;
  if(c.conj.size() > 0)
    {
      for(i = (c.conj.begin()); i != (c.conj.end()); ++i)
	output << *i << endl; // print all
    }
  output << endl;
  return output;
}

#ifndef externo
int F;
struct rango rango_funcion;

time_t Inicio, Fin_opt;
char * archivo_configuracion;
char * archivo_resultados;

individuo optimo_global;
individuo optimo;
int semilla;

int ps;
float mr, cr;
int so, co, mo, eo;
int mutaciones, cruzamientos;

int iteracion, max_iter, evaluaciones, maximo_evaluaciones;
float aptitud_opt;
int iteracion_opt;
int evaluacion_opt;
ofstream resultados;
bool optimo_encontrado;

char * archivo_convergencia = "convergencia.dat";
#endif


int int_rand (int , int );
float float_rand (float , float );
void calcular_aptitud(individuo * );
void validar_permutacion(individuo * );
void escribir_en_archivo_resultados(individuo *);
void leer_archivo_configuracion(void);
void salir(void);
float absoluto( float );
float promedio(float , float );
