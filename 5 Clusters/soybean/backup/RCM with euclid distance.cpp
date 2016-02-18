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
 int array[376][35];
 
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
     
   
   /*
   for(int i=0;i<600;i++)
   { 
           printf("\narray no:%d ",i+1);
           for(int j=0;j<60;j++)
           {
                   printf("%lf ",data[i][j]);
           }
   }*/
 //FILE READING COMPLETE
 
    int c_approx[2][5][376];
    double c_means[35][5],distance[376][5],c_distance[5][5],U[376][5],diff[376],x_bar[376],addition=0.0,sig_square,dist=0.0;
    int temp;

    
    for(int i=0;i<35;i++)
    {printf("\n");
            for(int j=0;j<5;j++)
            {
                    c_means[i][j]=(double)array[j][i];
                    printf("%lf ",c_means[i][j]);
            }
    }
 //generated random means                     

  for(int i=0;i<2;i++)
    {
            for(int j=0;j<5;j++)
            {
                    for(int k=0;k<376;k++)
                    {
                    c_approx[i][j][k]=-1;
                    }
            }
    }
  //initialized c_approx
  
   for(int i=0;i<376;i++)
  {
          for(int j=0;j<5;j++)
          {
                  distance[i][j]=0.0;  
           }
           
  }
  
  //initialized distance matrix with 0 
  
   for(int y=0;y<5;y++)
   {
           c_approx[0][y][0]=y;
           c_approx[1][y][0]=y;
           
           
   }
   
   for(int p=0;p<35;p++)
   {
           for(int i=0;i<376;i++)
           {
                   addition+=(double)array[i][p];
           }
           x_bar[p]=addition;
           x_bar[p]=x_bar[p]/376.0;
   }
   
   for(int i=0;i<376;i++)
   {       double comp=0.0;
           for(int k=0;k<35;k++)
           {
                   comp+=pow(((double)array[i][k]-x_bar[k]),2);
           }
           dist+=comp;
   }
   sig_square=dist/376.0;
          
  
  for(index=5;index<376;index++)
  {       
          printf("\n\nFOR POINT=%d\n",index+1);
          for(int j=0;j<5;j++)
          {
                  for(int k=0;k<35;k++)
                  {       
                          distance[index][j]+=pow(((double)array[index][k]-c_means[k][j]),2);
                  }
                  distance[index][j]=sqrt(distance[index][j]);
                  
          }
          
         
          int min1=0,min2=0;
          for(int a=0;a<5;a++)
          {
                  if(distance[index][a]<distance[index][min1])
                  min1=a;
          }
          if(min1==0)
          min2=1;        
          for(int a=0;a<5;a++)
          {
                  if(distance[index][a]<distance[index][min2] && min1!=a)
                  min2=a;
          }
          diff[index]=distance[index][min2]-distance[index][min1];
          printf("\nmin1 is %d",min1);
          printf("\nmin2 is %d",min2);
          if((distance[index][min2]-distance[index][min1])<0.9)
          {
                  int flag=0;
                  while(c_approx[1][min1][flag]!=-1)
                  flag++;
                  c_approx[1][min1][flag]=index;
                    
                  for(int p=0;p<35;p++)    
                  {       
                          count1=-1;
                          count2=-1;
                          sum1=0.0;
                          sum2=0.0;
                          sum2a=0.0;
                          
                          while((c_approx[0][min1][++count1])!=-1 && count1<376)  //lower
                          sum1+=(double)array[c_approx[0][min1][count1]][p];
                          
                          while(c_approx[1][min1][++count2]!=-1 && count2<376)   //upper
                          {
                          
                          sum2+=(double)(array[c_approx[1][min1][count2]][p]);
                          
                          
                          }
                          
                          //case1:::
                          if(count1!=0 && abs(count2-count1)!=0)
                          c_means[p][min1]=((w_low*sum1)/((double)count1))+((w_up*sum2)/abs(count2-count1)); 
                          
                          //case2:::
                          else
                          c_means[p][min1]=((double)sum1/(double)count1);
                          
                  }
                                         
                  flag=0;
                  while(c_approx[1][min2][flag]!=-1)
                  flag++;
                  c_approx[1][min2][flag]=index;
                                    
                  for(int p=0;p<35;p++)    
                  {       
                          count1=-1;
                          count2=-1;
                          sum1=0.0;
                          sum2=0.0;
                          sum2a=0.0;
                          while(c_approx[0][min2][++count1]!=-1 && count1<376)
                          sum1+=(double)array[c_approx[0][min2][count1]][p];
                          
                          while(c_approx[1][min2][++count2]!=-1 && count2<376)
                          {     
                                //printf("index of element is %d\n",c_approx[1][max2][count2]);
                                sum2=sum2+((double)array[c_approx[1][min2][count2]][p]);
                                
                                
                          }
                          //case1:::
                          if(count1!=0 && abs(count2-count1)!=0)
                          c_means[p][min2]=((w_low*sum1)/((double)count1))+((w_up*sum2)/abs(count2-count1));
                                  
                          //case2:::
                          else
                          c_means[p][min2]=((double)sum1/(double)count1);
                          
                          
                  }
                  
          }
                         
          else
          {
                  int flag=0;
                  while(c_approx[0][min1][flag]!=-1)
                  flag++;
                  c_approx[0][min1][flag]=index;
                  
                  
                  for(int p=0;p<35;p++)    
                  {       
                          count1=-1;
                          count2=-1;
                          sum1=0.0;
                          sum2=0.0;
                          sum2a=0.0;
                          while(c_approx[0][min1][++count1]!=-1 && count1<376)
                          sum1+=(double)array[c_approx[0][min1][count1]][p];
                          
                          while(c_approx[1][min1][++count2]!=-1 && count2<376)
                          {
                          //printf("index of elemnt is %d\n",c_approx[1][max1][count2]);
                          sum2+=(double)(array[c_approx[1][min1][count2]][p]);
                          
                          
                          }
                          //case1:::
                          if(count1!=0 && (count2-count1)!=0)
                          c_means[p][min1]=((w_low*sum1)/((double)count1))+((w_up*sum2)/abs(count2-count1));       
                          //case2:::
                          else
                          c_means[p][min1]=((double)sum1/(double)count1);
                          
                  }
                  
          }
           /*  
          for(int i=0;i<60;i++)
          {
            printf("\n");
            for(int j=0;j<6;j++)
            {
                    
                    printf(" %lf",c_means[i][j]);                                    
            }

            } */  
            //if(index==5)
            //break;
  }

  
  FILE *fs = fopen("C:\\Users\\dishant\\Desktop\\upper_approx.csv", "w+");
  if(fs == NULL)
  {
        printf("Couldn't open file\n");
        return -1;    
  }
  FILE *fd = fopen("C:\\Users\\dishant\\Desktop\\lower_approx.csv", "w+");
  if(fs == NULL)
  {
        printf("Couldn't open file\n");
        return -1;    
  }
  
  for(int e=0;e<5;e++)
        {
                  printf("\nfor cluster %d the values in the lower approximation are ",e+1);
                  fprintf(fd,"Cluster=%d\n",e+1);
                  for(int w=0;w<376;w++)
                  {       if(c_approx[0][e][w]!=-1)
                          {
                          printf("%d ",c_approx[0][e][w]);
                          fprintf(fd,"%d\n",c_approx[0][e][w]);
                          }
                  }    
                  printf("\nfor cluster %d the values in the upper approximation are ",e+1);
                  fprintf(fs,"Cluster=%d\n",e+1);
                  for(int w=0;w<376;w++)
                  {       if(c_approx[1][e][w]!=-1)
                          {
                          printf("%d ",c_approx[1][e][w]);
                          fprintf(fs,"%d\n",c_approx[1][e][w]);
                          }
                  }
                  
        }
        
  fclose(fs);
  fclose(fd);
  
  double t1[4],db_index=0.0,d_index=0.0,t2[4],t3[5];
  printf("\n");
 /* for(int i=0;i<376;i++)
  {
          printf("\t%lf",diff[i]);
          s+=diff[i];
  }
  printf("\n%lf",s/376.0);*/
  
  //ACCURACY MEASURES
  double S[5];
  for(int i=0;i<5;i++)
  {
          count1=-1;
          count2=0;
          sum1=0.0;
          sum2=0.0;
          sum2a=0.0;
          double sum2=0.0,sum2a=0.0;
          while(c_approx[0][i][++count1]!=-1 && count1<376)
          sum1+=pow(distance[c_approx[0][i][count1]][i],2);
                          
          while(c_approx[1][i][++count2]!=-1 && count2<376)
          {
          sum2+=pow(distance[c_approx[1][i][count2]][i],2);
          
          }
                          //case1:::
          if(count2!=0 && abs(count2-count1)!=0)
          S[i]=((w_low*sum1)/((double)count2))+((w_up*sum2)/abs(count2-count1));
                                  
                          //case2:::
          else
          S[i]=(sum1/(double)count1);                                      
  }
  //for(int i=0;i<5;i++)
  //printf("\nS value is %lf",S[i]);
  
  for(int i=0;i<5;i++)
  {
          for(int j=0;j<5;j++)
          {
                  for(int k=0;k<35;k++)
                  {       
                          c_distance[i][j]+=pow((c_means[k][i]-c_means[k][j]),2);
                  }
                  c_distance[i][j]=sqrt(c_distance[i][j]);
          }
  }
  
   for(int i=0;i<5;i++)
   {
           int k=0; 
           for(int j=0;j<5;j++)
           {
                   if(i!=j)
                   {
                           t1[k++]=((S[i]+S[j])/c_distance[i][j]);
                   }
           }
           db_index+=max(t1,4);
           
   }
   db_index=db_index/5.0;
   printf("\nDB index is %lf",db_index); 
   
   int f=0;
   double max_S=max(S,5);
   for(int i=0;i<5;i++)
   { 
           int k=0;
           for(int j=0;j<5;j++)
           {
                   if(i!=j)
                   {       
                           t2[k++]=c_distance[i][j]/max_S;
                           
                   }
           }
           t3[f++]=min(t2,4);
   }
   d_index=min(t3,5);
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
