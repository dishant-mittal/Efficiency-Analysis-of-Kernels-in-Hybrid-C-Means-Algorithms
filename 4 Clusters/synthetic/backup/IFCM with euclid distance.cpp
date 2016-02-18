#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define ARRAYSIZE(x)  (sizeof(x)/sizeof(*(x)))
#include <math.h>
#include<string.h>
#include <iomanip>
#include <cstdlib>
#include <time.h>
 
double max(double [],int);
double min(double [],int);

 int in,index,count1,count2;
 double sum1,sum2,sum2a,pi,summation;
 double b,w_low=0.7,w_up=0.3;
 int array[600][120];
 double data[600][60];
 int record=0;
//declarations over   

int main(void)
{
   const char filename[] = "synthetic.csv";
  
   FILE *file = fopen(filename, "r");
   if ( file )
   {
      
      size_t i, j, k;
      char buffer[BUFSIZ], *ptr;
    
      for ( i = 0; fgets(buffer, sizeof buffer, file); ++i )
      {
         
         for ( j = 0, ptr = buffer; j < ARRAYSIZE(*array); ++j, ++ptr )
         {
            array[i][j] = (int)strtol(ptr, &ptr, 10);
         }
         
      }

      fclose(file);
     
      for ( j = 0; j < i; ++j )
      {
         printf("array[%lu]: ", (long unsigned)j);
         for ( k = 0; k < ARRAYSIZE(*array); ++k )
         {
            printf("%4d ", array[j][k]);
         }
          
         putchar('\n');
         in=i;
      }
     
   }
   else 
   {
      perror(filename);
   } 
   for(int i=0;i<600;i++)
   { 
           record=0;
           for(int j=0;j<119;j++)
           {
                   data[i][record++]=((double)array[i][j]+((double)array[i][j+1]/10000.0));
                   j++;
           }
   }
 //FILE READING COMPLETE
    int c_approx[2][4][600];
    double c_means[60][4],distance[600][4],c_distance[4][4],U[600][4],diff[600];
    int temp;

    
    for(int i=0;i<60;i++)
    {
            for(int j=0;j<4;j++)
            {
                    c_means[i][j]=data[j][i];
            }
    }
 //generated random means                     

  for(int i=0;i<2;i++)
    {
            for(int j=0;j<4;j++)
            {
                    for(int k=0;k<600;k++)
                    {
                    c_approx[i][j][k]=-1;
                    }
            }
    }
  //initialized c_approx
  
   for(int i=0;i<600;i++)
  {
          for(int j=0;j<4;j++)
          {
                  distance[i][j]=0.0;
                  
           }
           
  }
  
  //initialized distance matrix with 0 
  //double r,e;
  for(int i=0;i<600;i++)
  {       
          
   
           U[i][0]= 0.0 + (0.25 - 0.0) * rand() / ((double) RAND_MAX);
           U[i][1]=0.5-U[i][0];
           U[i][2]=0.0 + (0.25 - 0.0) * rand() / ((double) RAND_MAX);
           U[i][3]=0.5-U[i][2];
           
   
}
   for(int i=0;i<600;i++)
  {       
          printf("\n");
                  printf("%lf ",U[i][0]+U[i][1]+U[i][2]+U[i][3]);
  }
  
   
   
        
  
  for(index=4;index<600;index++)
  {       
          //printf("\n\nFOR POINT=%d\n",index+1);
          for(int j=0;j<4;j++)
          {
                  for(int k=0;k<60;k++)
                  {       
                          distance[index][j]+=pow((data[index][k]-c_means[k][j]),2);
                  }
                  distance[index][j]=sqrt(distance[index][j]);
          }
          
          for(int j=0;j<4;j++)
          {
                  if(distance[index][j]==0)
                  U[index][j]=1.0;
                  else
                  {
                      summation=0.0;
                      for(int k=0;k<4;k++)
                      {
                           summation+=pow((distance[index][j])/(distance[index][k]),2);
                      }
                      U[index][j]=1/summation;
                  }
                  pi=0.0;
                  pi=1.0-U[index][j]-((1.0-U[index][j])/(1.0+2.0*U[index][j]));
                  U[index][j]=U[index][j]+pi;
          }
          
          for(int y=0;y<4;y++)
          {
                  for(int p=0;p<60;p++)    
                  {       
                          sum1=0.0;
                          sum2=0.0;
                          for(int i=0;i<600;i++)
                          {
                                  sum1+=pow(U[i][y],2)*data[i][p];
                                  sum2+=pow(U[i][y],2);
                          }
                          c_means[p][y]=sum1/sum2; 
                  }
          }
          
  }
  
  for(int i=0;i<600;i++)
  {
          int max1=0;
          for(int a=0;a<4;a++)
          {
                  if(U[i][a]>U[i][max1])
                  max1=a;
          }
          int flag=0;
          while(c_approx[0][max1][flag]!=-1)
          flag++;
          c_approx[0][max1][flag]=i;
  }

  
  FILE *fs = fopen("C:\\Users\\dishant\\Desktop\\membership.csv", "w+");
  if(fs == NULL)
  {
        printf("Couldn't open file\n");
        return -1;    
  }
  
  
  for(int e=0;e<4;e++)
        {
                  printf("\nfor cluster %d the values are ",e+1);
                  fprintf(fs,"Cluster=%d\n",e+1);
                  for(int w=0;w<600;w++)
                  {       if(c_approx[0][e][w]!=-1)
                          {
                          printf("%d ",c_approx[0][e][w]);
                          fprintf(fs,"%d\n",c_approx[0][e][w]);
                          }
                  }    
                  
        }
  fclose(fs);
  
  double t1[3],db_index=0.0,d_index=0.0,t2[3],t3[4];
  printf("\n");
 /* for(int i=0;i<376;i++)
  {
          printf("\t%lf",diff[i]);
          s+=diff[i];
  }
  printf("\n%lf",s/376.0);*/
  
  //ACCURACY MEASURES
  double S[4];
  for(int y=0;y<4;y++)
  {
          sum1=0.0;
          sum2=0.0;
          for(int i=0;i<600;i++)
          {
                  sum1+=pow(U[i][y],2)*pow(distance[i][y],2);
                  sum2+=pow(U[i][y],2);
          }
          S[y]=sum1/sum2; 
                                               
  }
  //for(int i=0;i<4;i++)
  //printf("\nS value is %lf",S[i]);
  
  for(int i=0;i<4;i++)
  {
          for(int j=0;j<4;j++)
          {
                  for(int k=0;k<60;k++)
                  {       
                          c_distance[i][j]+=pow((c_means[k][i]-c_means[k][j]),2);
                  }
                  c_distance[i][j]=sqrt(c_distance[i][j]);
          }
  }
  
   for(int i=0;i<4;i++)
   {
           int k=0; 
           for(int j=0;j<4;j++)
           {
                   if(i!=j)
                   {
                           t1[k++]=((S[i]+S[j])/c_distance[i][j]);
                   }
           }
           db_index+=max(t1,3);
           
   }
   db_index=db_index/4.0;
   printf("\nDB index is %lf",db_index); 
   
   int f=0;
   double max_S=max(S,4);
   for(int i=0;i<4;i++)
   { 
           int k=0;
           for(int j=0;j<4;j++)
           {
                   if(i!=j)
                   {       
                           t2[k++]=c_distance[i][j]/max_S;
                           
                   }
           }
           t3[f++]=min(t2,3);
   }
   d_index=min(t3,4);
   printf("\nD index is %lf",d_index); 
   
                  
  getch();
  return 0;  

}

double max(double x[],int k)
{
	int i;
	double t;
	t=x[0];
	for(i=1;i<k;i++)
        {
		if(x[i]>t)
			t=x[i];
	}
	return(t);
}

double min(double x[],int k)
{
	int i;
	double t;
	t=x[0];
	for(i=1;i<k;i++)
        {
		if(x[i]<t)
			t=x[i];
	}
	return(t);
}
