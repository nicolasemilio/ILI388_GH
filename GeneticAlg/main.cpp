#include "includes.h"
#include "globales.h"

bool debug = true;

float absoluto(float a)
{
  if (a<0.0)
    return (-1*a);
  return a;
}

void inicializar_archivo_convergencia(void)
{
  FILE * conv;
  conv = fopen (archivo_convergencia, "w");
  fclose(conv);
  return;
}

void escribir_en_archivo_convergencia(void)
{
  FILE * conv;
  conv = fopen (archivo_convergencia, "a");
  fprintf(conv, "%d %.2f\n", iteracion, optimo.aptitud);
  fclose(conv);
}


//Seleccion de individuos//

individuo * roulette_wheel (conjunto & c_temp)
{
  int i = 0;
  float rand;
  float acumulado = 0.00, suma = 0.00;
  individuo * i_temp;

  //aptitud temporal de cada anticuerpo (problema de minimizacion)
  float aptitud_temporal[ps];
  
  sort(c_temp.conj.begin(), c_temp.conj.end());
  //se supone repertorio ordenado
  float maximo = c_temp.conj.back().aptitud;
  float minimo = c_temp.conj.front().aptitud;
  
  for (vector<individuo>::iterator p = c_temp.conj.begin (); p != c_temp.conj.end (); p++)
    {
      //calculo de la aptitud temporal de cada anticuerpo del repertorio
      aptitud_temporal[i] = minimo + maximo - (p->aptitud); //version2.0 de minimizacion
      suma += aptitud_temporal[i];
      i++;
    }
  //la suma de la aptitud de todos los individuos no puede ser cero
  if(suma == 0)
    {
      cout<<"ERROR: Condicion extraña en seleccionar individuo"<<endl;
      i_temp = (&(c_temp.conj.front()));
      return i_temp;
    }
  //numero aleatorio para la ruleta
  rand = float_rand(0.00, suma);
  i=0;
  
  //busqueda del anticuerpo en la ruleta
  for (vector<individuo>::iterator p = c_temp.conj.begin (); p != c_temp.conj.end (); p++)
    {
      acumulado += aptitud_temporal[i];
      i++;
      if (acumulado > rand)
	{
	  i_temp = &(*p);
	  return i_temp;
	}
    }
  //en caso de ser el ultimo anticuerpo del repertorio
  i_temp = (&(c_temp.conj.back()));
  return i_temp;
}

individuo * ranking (conjunto & c_temp)
{
  individuo * i_temp;
  int ranking = 0;
  int rand, acumulado = 0;
  
  ranking = c_temp.conj.size();
  int total = (c_temp.conj.size()*(c_temp.conj.size()+1))/2;
  rand = int_rand(0, total+1);
  sort(c_temp.conj.begin(), c_temp.conj.end());
  
  for (vector<individuo>::iterator p = c_temp.conj.begin (); p != c_temp.conj.end (); p++)
    {
      acumulado += ranking;
      if (acumulado >= rand)
	{
	  i_temp = &*p;
	  return i_temp;
	}
      ranking--;
    }
  //en caso de ser el ultimo anticuerpo del repertorio
  i_temp = &(c_temp.conj.back());
  return i_temp;
}

individuo * tournament (conjunto & c_temp)
{
  int rand1, rand2;
  individuo * i_temp;
  
  sort(c_temp.conj.begin(), c_temp.conj.end());
  
  //numero aleatorio para la ruleta
  rand1 = int_rand(0, c_temp.conj.size());
  rand2 = int_rand(0, c_temp.conj.size());
  int i=0;
  int buscar;

  if((c_temp.conj[rand1].aptitud) < (c_temp.conj[rand2].aptitud))
    {
      buscar = rand1;
    }
  else
    {
      buscar = rand2;
    }
  
  //busqueda del individuo en la ruleta
  for (vector<individuo>::iterator p = c_temp.conj.begin (); p != c_temp.conj.end (); p++)
    {
      if(i==buscar){
	i_temp = &(*p);
	return i_temp;
      }
      i++;
    }
  //en caso de ser el ultimo anticuerpo del repertorio
  i_temp = (&(c_temp.conj.back()));
  return i_temp;
}

individuo * seleccionar_individuo (conjunto & c_temp)
{
  individuo * i_temp;
  switch(so)
    {
      case ROULETTE:
	{
	  i_temp = roulette_wheel(c_temp);
	  return i_temp;
	}
    case TOURNAMENT:
      {
	i_temp = tournament(c_temp);
	return i_temp;
      }
    case RANKING:
      {
	i_temp = ranking(c_temp);
	return i_temp;
      }
    default:
      {
	cout<<"ERROR: No se reconoce tipo de seleccion"<<endl;
	salir();
      } 
   }
}

void seleccionar_conjunto(conjunto & in, conjunto & out, int n)
{
  individuo * p_i_temp;
  for(int i=0; i<n; i++)
    {
      individuo i_temp;
      p_i_temp = seleccionar_individuo(in);
      i_temp = *p_i_temp;
      out.conj.push_back(i_temp);
    }
}

//Mutacion de individuos//


void mutacionBitFlip(individuo * padre, individuo * hijo)
{

  *hijo = *padre;
  int rand;
  
  //revisar para cada bit la probabilidad de cambio
  for(int i=0; i < (Nvariables * Precision); i++)
  {
    if(float_rand(0.00, 1.00)<mr)
      hijo->cromosoma[i] = 1 - padre->cromosoma[i];
  }

  hijo->usado = true;
  calcular_aptitud(hijo);
  mutaciones++;
  return;
}

void seleccionar_dos_puntos_de_corte(int *corte1, int *corte2, int maximo)
{
  //seleccionar dos puntos de corte diferentes entre variables
  int c1, c2, aux;
  c1=int_rand(0, maximo); //entre 0 y maximo
  do{
    c2=int_rand(0, maximo);
  }while(c1==c2);

  //revisar condicion de c1 < c2
  if(c1 > c2){
    aux = c2;
    c2 = c1;
    c1=aux;
  }

  *corte1 = c1;
  *corte2 = c2;
  return;
}

void mutacionInOrder(individuo * padre, individuo * hijo)
{
  *hijo = *padre;
  int rand;

  //seleccionar dos puntos de corte diferentes entre variables
  int corte1, corte2;
  seleccionar_dos_puntos_de_corte(&corte1, &corte2, Nvariables*Precision);
  
  //revisar para cada bit la probabilidad de cambio
  for(int i=corte1; i < corte2; i++)
  {
    if(float_rand(0.00, 1.00)<mr)
      hijo->cromosoma[i] = 1 - padre->cromosoma[i]; //version2.0
  }
  
  hijo->usado = true;
  calcular_aptitud(hijo);
  mutaciones++;
  return;
}

void mutar_individuo(individuo * padre, individuo * hijo, float mr)
{
  *hijo = *padre;
    switch(mo)
    {
      case BITFLIP:
      {
	mutacionBitFlip(padre, hijo);
	return;
      }
      case INORDER:
      {
	mutacionInOrder(padre, hijo);
	return;
      }
      default:
      {
	cout<<"ERROR: No se reconoce tipo de mutacion"<<endl;
	salir();
      }
    }
    //}
  return;
}

void mutar_conjunto(conjunto & in, conjunto & out, float mr)
{
  individuo * p_seleccionado;
  for (vector<individuo>::iterator p = in.conj.begin (); p != in.conj.end (); p++)
    {
      individuo mutado;
      p_seleccionado = &*p;
      mutar_individuo(p_seleccionado, &mutado, mr);
      calcular_aptitud(&mutado);
      out.conj.push_back(mutado);
    }
  return;
}

void guardar_optimo_encontrado (int aptitud_optimo, individuo temp)
{
  //recuerda el optimo encontrado
  optimo.aptitud = aptitud_optimo;
  iteracion_opt = iteracion;
  evaluacion_opt = evaluaciones;
  optimo_encontrado = true;
  //muestra el individuo encontrado como optimo
  if(debug)
  {
      cout<<endl<<"Aptitud: "<<aptitud_optimo;
  }
  salir();
  return;
}

void escribir_en_archivo_resultados(individuo * optimo)
{
  //escritura en el archivo de resultados
  //calculo de tiempo de ejecucion del algoritmo
  //time_t Fin;
  //Fin=time(NULL);
  FILE * res;
  res = fopen (archivo_resultados, "a");
  
  //calculo de evaluaciones para tuning
  if(optimo_encontrado)
    fprintf(res, "%d\n", evaluaciones);
  else
    fprintf(res, "%d\n", maximo_evaluaciones);
 
  //SPOT
  if(optimo_encontrado)
    printf("%d\n", evaluaciones);
  else
    printf("%d\n", maximo_evaluaciones);
  
  
  //fprintf(res, "%d %d %d %d %d %d %d\n", optimo->aptitud, evaluacion_opt, evaluaciones, iteracion_opt, iteracion, (int)(Fin_opt-Inicio), (int)(time(NULL)- Inicio));
  //fprintf(res, "%.2f \n", optimo->aptitud);
  
  fclose(res);
  return;
}

int Codigo_Gray(int * lista_gray)
{
  int resultado=0;
  int * lista_bin;
  lista_bin = new (int[Precision]);
  lista_bin[0] = lista_gray[0];
  int anterior = lista_bin[0];
  
  for(int i=1; i<Precision; i++)
    {
      //desde el elemento 1, pues el elemento 0 se conserva
      switch((anterior + lista_gray[i]))
	{
	case 0:
	  {
	    lista_bin[i] = 0;
	    break;
	  }
	case 1:
	  {
	    lista_bin[i] = 1;
	    break;
	  }
	case 2:
	  {
	    lista_bin[i] = 0;
	    break;
	  }
	default: 
	  {
	  cout<<"ERROR: problemas en lectura de codigo gray";
	  exit(0);
	  }
	}
      anterior = lista_bin[i];
    }
  //traduccion desde binario a decimal
  for(int i=0; i<Precision; i++)
      resultado += (int)(lista_bin[i] * (pow(2, (Precision - i -1))));
  
  delete[] lista_bin;
  
  //retorno del valor decimal (No rankeado)
  return resultado;
}

float rankear(int binario)
{
  float resultado = rango_funcion.minimo + binario*(V);
  if(resultado < rango_funcion.minimo) resultado = rango_funcion.minimo;
  if(resultado > rango_funcion.maximo) resultado = rango_funcion.maximo;
  return resultado;
}


void traducir_individuo(individuo * temp)
{
  vector <int> individuo_gray;
  individuo_gray = temp->cromosoma;
  
  int * variable_gray;
  variable_gray = new(int[Precision]);
  
  for(int i=0; i<Nvariables; i++)
    {
      //copia de cada variable desde individuo_gray en variable_gray
      for(int j=0; j<Precision; j++)
	{ 
	  variable_gray[j] = individuo_gray[(i*Precision) + j];
	}
      //traduccion a binario
      temp->cromosoma_binario[i] = Codigo_Gray(variable_gray);
      //traduccion a entero
      temp->cromosoma_real[i] = rankear(temp->cromosoma_binario[i]);
    }
  delete[] variable_gray;
  
  return;
}


void sphere(individuo * temp)
{
  float apt = 0.00, var;

  for(int i = 0; i < Nvariables; i++)
    {
      var = temp->cromosoma_real[i];
      apt += pow(var, 2);
    }

  if(apt <= Optimof1) guardar_optimo_encontrado(apt, *temp);
  
  temp->aptitud = apt;
  return;
}

void rosembrock(individuo * temp)
{
  float apt = 0.00;
  float var1 = temp->cromosoma_real[0];
  float var2 = temp->cromosoma_real[1];

  apt = 100*pow((var2 - pow(var1,2)), 2) + pow((1 - var1),2);

  if(apt <= Optimof1) guardar_optimo_encontrado(apt, *temp);
   
  temp->aptitud = apt;
  return;
}

void step(individuo * temp)
{
  float apt = 6.00*Nvariables, var;

  for(int i=0; i < Nvariables; i++)
    {
      var = temp->cromosoma_real[i];
      apt += (int)floor(var);
    }

  if(apt <= Optimof1) guardar_optimo_encontrado(apt, *temp);
  
  temp->aptitud = apt;
  return;
}

void schaffer(individuo * temp)
{
  float apt = 0.00;
  
  float var1 = temp->cromosoma_real[0];
  float var2 = temp->cromosoma_real[1];
  
  float numerador = pow(sin(sqrt(pow(var1,2) + pow(var2,2))),2) - 0.5;
  float denominador = pow((1.00+0.0001*(pow(var1,2) + pow(var2,2))),2);
  apt = 0.50 + (numerador)/(denominador);
  
  if(apt <= Optimof4) guardar_optimo_encontrado(apt, *temp);
 
  temp->aptitud = apt;
  return;
}

void rastrigin(individuo * temp)
{
  float apt = 0.00, w = 2*PI, var;
  int A = 10;
  
  apt += A*Nvariables;
  
  for(int i = 0; i < Nvariables; i++)
    {
      var = temp->cromosoma_real[i];
      apt += pow(var, 2) - A*cos(w*(var));
    }
    
  if(apt <= Optimof5) guardar_optimo_encontrado(apt, *temp);
  
  temp->aptitud = apt;
  return;
}

void schwefel(individuo * temp)
{
  float apt = 0.00, var;
  
  for(int i=0; i< Nvariables; i++)
    {
      var = temp->cromosoma_real[i];
      apt +=  -1*var*sin(sqrt(absoluto(var)));
    }
  apt += 418.9829 * Nvariables;

  if(apt <= Optimof6) guardar_optimo_encontrado(apt, *temp);
    
  temp->aptitud = apt;
  return;
}

void griewank(individuo * temp)
{
  float apt = 0.00, suma=0.00, multiplicacion=1.00, var;
  apt += 1.00;

  for(int i=0; i<Nvariables; i++)
    {
      var = temp->cromosoma_real[i];
      suma += (pow(var, 2)/4000);
      multiplicacion *= cos(var/sqrt(i+1));
    }
  apt = apt + suma - multiplicacion;
  
  if(apt <= Optimof6) guardar_optimo_encontrado(apt, *temp);

  temp->aptitud = apt;
  return;
}

void ackley(individuo *temp)
{
  float apt = 0.00, norma = 0.00, suma_coseno = 0.00, var;
  
  for(int i=0; i < Nvariables; i++)
    {
      var = temp->cromosoma_real[i];
      norma += pow(var, 2);
      suma_coseno += cos(2*PI*var);
    }
    
  apt= -20.00*exp(-0.2*sqrt((1.00/Nvariables) * norma)) - exp((1.00/Nvariables)*suma_coseno) + 20.00 + exp(1.00);
  
  if(apt <= Optimof5) guardar_optimo_encontrado(apt, *temp);
  
  temp->aptitud = apt;
  return;
}

void calcular_funcion(individuo * individuo_temp)
{
  switch(F)
  {
    case 1:
      sphere(individuo_temp); return;
    case 2:
      rosembrock(individuo_temp); return;
    case 3:
      step(individuo_temp); return;
    case 4:
      schaffer(individuo_temp); return;
    case 5:
      rastrigin(individuo_temp); return;
    case 6:
      schwefel(individuo_temp); return;
    case 7:
      griewank(individuo_temp); return;
    case 8:
      ackley(individuo_temp); return;
    default:
      {
	cout<<"ERROR: La funcion especificada no existe"<<endl;
	salir();
      }
    }
}

float retornar_optimo_funcion(int F)
{
  switch(F)
    {
    case 1:
    case 2:
    case 3:
      {
	return Optimof1;
      }
    case 4:
      {
	return Optimof4;
      }
    case 5:
    case 6:
  case 7: 
    case 8:
      {
	return Optimof5;
      }
    default:
      {
	cout<<"ERROR: No se reconoce la funcion"<<endl;
	salir();
      }
    }
}


void calcular_aptitud(individuo * temp)
{
  //Reevaluar solo los individuos con cambios
  if(temp->usado==false) 
    {
      return;   
    }
  temp->usado=false;

  traducir_individuo(temp);
  calcular_funcion(temp);

  //conteo de la cantidad de evaluaciones realizadas en el algoritmo
  evaluaciones++;
  //chequeo de maximo de evaluaciones
  if(evaluaciones >= maximo_evaluaciones)
    {
      salir();
    }
  return;
}


void leer_archivo_configuracion(void){
  /*lectura de archivo de configuracion*/
  int i, j, k;
  ifstream configuracion;
  configuracion.open(archivo_configuracion);
  /*identificador numerico de la funcion a evaluar*/
  configuracion >> F;
  /*cantidad de variables a considerar*/
  configuracion >> Nvariables;
  /*precision de la representacion binaria*/
  configuracion >> Precision;
  /*valor minimo que pueden tomar las variables*/
  configuracion >> rango_funcion.minimo;
  /*valor maximo que pueden tomar las variables*/
  configuracion >> rango_funcion.maximo;

  /*calculo de V para transformacion de valores enteros al rango adecuado*/
  V = ((rango_funcion.maximo - rango_funcion.minimo) / (pow(2, Precision) - 1)); //version2.0
  optimo_global.aptitud = retornar_optimo_funcion(F);
  return;
}



void agregar_individuo_aleatorio (conjunto & c_temp)
{
  int rand;
  individuo i_temp;
  i_temp.usado = true;
  
  for (int i = 0; i < Nvariables; i++)
  {
    for(int j = 0; j < Precision; j++)
    {
       rand = int_rand (0, 2); // Un valor entre 0 y 1
       i_temp.cromosoma[(Precision)*i+j] = rand; 
    }
  }
  //calculo de la aptitud del individuo
  calcular_aptitud (&i_temp);

  c_temp.conj.push_back (i_temp);
  return;
}

void crear_poblacion_inicial (conjunto & c_temp, int size)
{
  for (int i=0; i<size; i++)
    {
      agregar_individuo_aleatorio(c_temp);
    }
  return;
}

int int_rand (int a, int b)
{
  //generacion de numeros aleatorios entre a y b-1
  int retorno = 0;
  if (a < b)
    { 
      //retorno cuando a < b
      retorno = (int) ((b - a) * drand48 ());
      retorno = retorno + a;
    }
  else
    {
      //retorno cuando b <= a
      retorno = (int) ((a - b) * drand48 ());
      retorno = retorno + b;
    }
  return retorno;
}

float float_rand (float a, float b)
{
  //generacion de numeros aleatorios entre a y b-1
  float retorno = 0.00;
  if (a < b)
    {
      //retorno cuando a < b
      retorno = ((b - a) * drand48 ());
      retorno = retorno + a;
    }
  else
    {
      //retorno cuando b <= a
      retorno = ((a - b) * drand48 ());
      retorno = retorno + b;
    }
  return retorno;
}

void salir(void)
{
  escribir_en_archivo_resultados(&optimo);
  //salida sin error
  exit(0);
  return;
}

void guardar_optimo(conjunto & c_temp)
{
  sort(c_temp.conj.begin(), c_temp.conj.end());
  if(c_temp.conj.front().aptitud < optimo.aptitud)
    {
      optimo = c_temp.conj.front();
      iteracion_opt = iteracion;
      evaluacion_opt = evaluaciones;
      Fin_opt = time(NULL);
      //cout<<iteracion<<" "<< optimo.aptitud<<endl;
     // escribir_en_archivo_convergencia();
    }
  //Si se cumplen 500000 evaluaciones ~ 100 iteraciones sin cambio se acaba
  if((evaluaciones - evaluacion_opt)>1000000)
  //if(iteracion - iteracion_opt > 100)	  
  {
  	salir();
  }
  return;
}

void cruzamientoEnDosPuntos(individuo * padre1, individuo * padre2, individuo * hijo1, individuo * hijo2)
{

  //copiar padre1 en hijo1 y padre2 en hijo2
  *hijo1 = *padre1;
  *hijo2 = *padre2;

  //seleccionar dos puntos de corte diferentes entre variables
  int corte1, corte2;
  seleccionar_dos_puntos_de_corte(&corte1, &corte2, Nvariables);
  
  //intercambiar la informacion entre corte1*Precision y corte2*Precision
  for(int i=corte1*Precision; i < corte2*Precision; i++)
  {
    //poner lo de padre2 en hijo1
    hijo1->cromosoma[i] = padre2->cromosoma[i];
    //poner lo de padre1 en hijo2
    hijo2->cromosoma[i] = padre1->cromosoma[i];
  }

  //Conteo y reevaluacion
  cruzamientos++;
  hijo1->usado = true;
  hijo2->usado = true;

  calcular_aptitud (hijo1);
  calcular_aptitud (hijo2);

  return;
}


void cruzamientoEnUnPunto(individuo * padre1, individuo * padre2, individuo * hijo1, individuo * hijo2){


  //copiar padre1 en hijo1 y padre2 en hijo2
  *hijo1 = *padre1;
  *hijo2 = *padre2;

  //seleccion del punto de corte
  int corte = int_rand(0, Nvariables);
  
  for (int i=corte*Precision; i<Nvariables*Precision; i++){
    //intercambio de la informacion desde corte en adelante
    hijo1->cromosoma[i] = padre2->cromosoma[i];
    hijo2->cromosoma[i] = padre1->cromosoma[i];
  }

  cruzamientos++;
  hijo1->usado = true;
  hijo2->usado = true;

  calcular_aptitud (hijo1);
  calcular_aptitud (hijo2);

  return;
}



void cruzar_individuos(individuo * padre1, individuo * padre2, individuo * hijo1, individuo * hijo2)
{
  if(float_rand(0.00, 1.00)<cr)
    {
      switch(co)
	{
	  case DOSPUNTOS:
	    {
	      cruzamientoEnDosPuntos(padre1, padre2, hijo1, hijo2);
	      return;
	    }
	  case UNPUNTO:
	    {
	      cruzamientoEnUnPunto(padre1, padre2, hijo1, hijo2);
	      return;
	    }
	  default:
	    {
	      cout<<"ERROR: No se reconoce tipo de cruzamiento"<<endl;
	      salir();
	    }
	}
   }
  else
  {
    *hijo1 = *padre1;
    *hijo2 = *padre2;
  }
}

void cruzar_conjunto(conjunto & in, conjunto & out, int n)
{
  individuo * padre1;
  individuo * padre2;
  individuo hijo1, hijo2;
  for (vector<individuo>::iterator p = in.conj.begin (); p != in.conj.end (); p++)
    {
      padre1 = &(*p);
      p++;
      if(p==in.conj.end ())
      {
	hijo1=*padre1;
	out.conj.push_back(hijo1);
	if(out.conj.size() == ps)
	  {
	    return;
	  }
      }
      else{
	padre2 = &(*p);
	cruzar_individuos(padre1, padre2, &hijo1, &hijo2);
	out.conj.push_back(hijo1);
	out.conj.push_back(hijo2);
       }
    }
}

static void control_c (int signo)
{
  //escribir_en_archivo_resultados(&optimo);
  exit (1);
}

int Leer_entradas(int argc, char **argv)
{
  //archivo con la instancia del problema
  archivo_configuracion = (char *)(argv[1]);
  //archivo donde escribir los resultados de la ejecucion
  archivo_resultados = (char *)(argv[2]);
  
  //PARAMETROS
  so = atoi(argv[3]); //selection operator 
  co = atoi(argv[4]); //crossover operator
  mo = atoi(argv[5]); //mutation operator
  eo = 1;
  cr = atof(argv[6]); //crossover rate
  mr = atof(argv[7]); //mutation rate
  ps = atoi(argv[8]); //population size
  if(debug)
  {
    printf("so: %d, mo: %d, co: %d, mr: %.2f, cr: %.2f, ps: %d\n", so, mo, co, mr, cr, ps);
    //getchar();
  }
  //BUDGET
  max_iter = (int)(atof(argv[9]));
  maximo_evaluaciones = max_iter;
  //SEMILLA
  semilla = atoi (argv[10]);
  return 1;
}


int main (int argc, char *argv[])
{
  struct timeval hora;
  
  if (signal (SIGINT, control_c) == SIG_ERR)
    printf ("can't catch SIGTERM");
  
  //lectura de parametros
  if(!Leer_entradas(argc,argv))
    {
      cout<<"Problemas en la lectura de los parametros";
      exit(1);
    }

  //lectura de instancia
  iteracion = -1;
  leer_archivo_configuracion();
  optimo_encontrado = false;
  evaluaciones = 0;

  //medicion de tiempo
  Inicio=time(NULL);

  //semilla aleatoria
  srand48 (semilla);

  //creacion de poblacion inicial aleatoria
 // inicializar_archivo_convergencia();
  conjunto poblacion ((char*)"poblacion");
  crear_poblacion_inicial(poblacion, ps);

  /*if(debug)
    {
      cout<<poblacion;
      //getchar();
    }*/
  //contador de hipermutaciones
  mutaciones=0;
  //int evaluaciones_ant = 0;
  //int prom_it;
  for (iteracion = 0; iteracion < max_iter; iteracion++)
    {
      time_t ini_it=time(NULL);
      conjunto seleccionados ((char*)"seleccionados");
      conjunto cruzados ((char*)"cruzados");
      conjunto mutados ((char*)"mutados");

      seleccionar_conjunto(poblacion, seleccionados, ps);
      /*if(debug)
	{
	  cout<<seleccionados;
	  getchar();
	}*/
      cruzar_conjunto(seleccionados, cruzados, cr);
      /*if(debug)
	{
	  cout<<"POBLACION CRUZADA"<<endl;
	  cout<<cruzados;
	  getchar();
	}*/
      mutar_conjunto(cruzados, mutados, mr);


        if(eo==1)
	  {
	    mutados.conj.front() = *&(poblacion.conj.front());
	  }
	poblacion.vaciar();
	poblacion = mutados;
        if(debug)
        {
            cout<<"ITERACION #" << iteracion <<endl;
            cout<<poblacion;
            //getchar();
        }
	strcpy(poblacion.name, "poblacion");
	seleccionados.vaciar();
	cruzados.vaciar();
	mutados.vaciar();
	guardar_optimo(poblacion);
    }    
  salir();
}
