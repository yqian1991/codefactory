#include <stdio.h>
#include <stdlib.h>
#include <math.h>   //used by sqrt math function

#define PI 3.141592653

double Pvcl[3];      //defined as global variable
double Pvcr[3];

double FC(double a, double b)
{
    double c=10.1f;
    /*
    *code here
    */
    return a+b;
}
//1, 2, 20, 10, 2
void VortexPointS(double m, double n, double M, double N, double SPC, double *Pvcl, double *Pvcr)
{
    //Pvcl[3]={0.0, 0.0, 0.0};
    //Pvcr[3]={0.0, 0.0, 0.0};

    double CU=(double)1/N;//0.1
    printf("CU=%f, \n", CU);
    double SU=(double)SPC/M;
    printf("SU=%f, \n", SU);//0.1

    Pvcl[0]=(m-1)*SU;//0
    printf("%f ", Pvcl[0]);
    Pvcl[1]=(n-0.75)*CU;//0.125
    printf("%f ", Pvcl[1]);
    Pvcl[2]=FC(Pvcl[0],Pvcl[1]);
    printf("%f \n", Pvcl[2]);

    Pvcr[0]=(m-1)*SU;//0
    Pvcr[1]=(n+0.25)*CU;//0.225
    Pvcr[2]=FC(Pvcr[0],Pvcr[1]);
    printf("%f ", Pvcr[0]);
    printf("%f ", Pvcr[1]);
    printf("%f ", Pvcr[2]);

}

double* CalKklmnc3(double *Pkl, double m, double n, double M, double N,double SPC)
{
    VortexPointS(m, n, M, N, SPC, Pvcl, Pvcr);

    double X1=Pvcl[0];//0
    double Y1=Pvcl[1];//0.125
    double Z1=Pvcl[2];//10.1

    double X2=Pvcr[0];//0
    double Y2=Pvcr[1];//0.225
    double Z2=Pvcr[2];//10.1

    double X=Pkl[0];
    double Y=Pkl[1];
    double Z=Pkl[2];

    double IA=sqrt((X2-X1)*(X2-X1)+(Y2-Y1)*(Y2-Y1)+(Z2-Z1)*(Y2-Y1));
    printf("IA=%f\n", IA);
    double IB=sqrt((X2-X)*(X2-X)+(Y2-Y)*(Y2-Y)+(Z2-Z)*(Z2-Z));
    printf("IB=%f\n", IB);
    double IC=sqrt( pow(X1-X ,2)+pow(Y1-Y, 2)+ pow(Z1-Z, 2));
    printf("IC=%f\n", IC);
    double IE=(double)(IA*IA-IB*IB+IC*IC)/(2*IA);
    printf("IE=%f\n", IE);
    double ID=sqrt(IC*IC-IE*IE);
    printf("ID=%f\n", ID);

    double IA3[3];
    IA3[0] = X2-X1;//0
    printf("IA3=%f\n", IA3[0]);
    IA3[1] = Y2-Y1;//0.1
    printf("IA3=%f\n", IA3[1]);
    IA3[2] = Z2-Z1;
    printf("IA3=%f\n", IA3[2]);

    double IC3[3];
    IC3[0] = X1-X;
    printf("IC3=%f\n", IC3[0]);
    IC3[1] = Y1-Y;
    IC3[2] = Z1-Z;

    double ID3[3];//=-IC3-(IE./IA).*IA3;
    int i=0;

    double temp = (double)IE/IA;
    for (i=0; i<3; i++)
    {
        ID3[i] = -IC3[i]-temp*IA3[i];
        printf("ID3[i]=%f\n", ID3[i]);
    }

    double V3[3];//=(1./(sqrt(dot(IA3,IA3)).*sqrt(dot(ID3,ID3)))).*cross(IA3,ID3);
    double dotIA3 = IA3[0]*IA3[0] + IA3[1]*IA3[1] + IA3[2]*IA3[2];
    double dotID3 = ID3[0]*ID3[0] + ID3[1]*ID3[1] + ID3[2]*ID3[2];
    double prefix = 1/(sqrt(dotIA3)*sqrt(dotID3));

    for (i=0; i<3; i++)
    {
        int j=i+1;
        if (j==3)
        {
            j=0;
        }
        double tempIAID3 = IA3[j]*ID3[3-i-j] - ID3[j]*IA3[3-i-j];
        printf("tempIAID3=%f\n", tempIAID3);
        V3[i] = prefix * tempIAID3;
        printf("V3=%f\n", V3);
    }

    double Kklmnc=((double)1/(4*PI*ID))*((double)IE/IC+(double)(IA-IE)/IB);
    printf("Kklmnc=%f\n", Kklmnc);
    //Kklmnc3=Kklmnc.*V3;
    double Kklmnc3[3];//=((float)1/(4*PI*ID))*((float)IE/IC+(float)(IA-IE)/IB)*V3;
    for (i=0; i<3; i++)
    {
        Kklmnc3[i] = Kklmnc*V3[i];
        printf("V3[i]=%f\n", V3[i]);
        printf("Kklmnc3=%f\n", Kklmnc3[i]);
    }
    double *result;
    result = Kklmnc3;
    return result;
}
int main()
{
    double Pkl[3]={2, 5, 8};
    double m=10;
    double n=2;
    double M = 20;
    double N= 10;
    double SPC = 2;
    double *result = CalKklmnc3(Pkl, m,  n,  M,  N, SPC);
    int i=0;
    for (i=0; i<3; i++)
    {
        printf("%f,",result[i]);
    }
    //printf("Hello world! %f\n", m/n);
    //printf("Hello world! %f\n", (double)m/sqrt(n));
    return 0;
}
