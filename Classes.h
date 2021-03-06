//---------------------------------------------------------------------------
#ifndef ClassesH
#define ClassesH
//---------------------------------------------------------------------------
#include "Definitions.h"
#include <stdio.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <math.h>
#define MAXDOUBLE 1000000
#define g_MaxTriangles 5
#define g_MaxSubdivisions 5
#define KEPSILON 0.00001
#define FLT_MAX     3.40282347E+38F
#include <fstream>

//---------------------------------------------------------------------------
struct julio {
    float x,y,z;                //arrive direction Vector
    float t;                    //arrive Time
    float e[NB];                //Energy [frequency band]
};
//---------------------------------------------------------------------------
class vector {

public:
    double x,y,z;

    void init(double a,double b, double c){
        x=a;
        y=b;
        z=c;
    };

    vector operator+(float distance){
        vector v1;
        v1.x=x+distance;
        v1.y=y+distance;
        v1.z=z+distance;
        return v1;
    };

    vector operator+(vector v2) { //soma
        vector v1;
        v1.x=x+v2.x;
        v1.y=y+v2.y;
        v1.z=z+v2.z;
        return v1;
    };
    vector operator-(vector v2) { //subtra��o
        vector v1;
        v1.x=x-v2.x;
        v1.y=y-v2.y;
        v1.z=z-v2.z;
        return v1;
    };
    vector operator*(double f) { //multiplica��o por escalar
        vector v;
        v.x=x*f;
        v.y=y*f;
        v.z=z*f;
        return v;
    };
    vector operator/(double f) { //divis�o por escalar
        vector v;
        v.x=x/f;
        v.y=y/f;
        v.z=z/f;
        return v;
    };
    double operator*(vector v) { //produto scalar
        double f;
        f= x*v.x + y*v.y + z*v.z;
        return f;
    };
    vector operator/(vector v2) { //produto vetorial
        vector v1;
        v1.x= y*v2.z-z*v2.y;
        v1.y=-x*v2.z+z*v2.x;
        v1.z= x*v2.y-y*v2.x;
        return v1;
    };
    void operator*=(double f) {
        x*=f;
        y*=f;
        z*=f;
    };
    void operator/=(double f) {
        x/=f;
        y/=f;
        z/=f;
    };
    void operator=(double f) {  //mesmo valor para x, y e z
        x=y=z=f;
    };

    bool operator==(vector v) { //igualdade entre vetores
        if(x==v.x&&y==v.y&&z==v.z)
            return 1;
        else
            return 0;
    };
    bool operator!=(vector v) { //desigualdade entre vetores
        if(x==v.x&&y==v.y&&z==v.z)
            return 0;
        else
            return 1;
    };
    double Angle(vector v) { //�ngulo entre dois vetores
        double angle,f;
        f=x*v.x+y*v.y+z*v.z; // produto escalar
        f/=sqrt(x*x + y*y + z*z);
        f/=sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
        angle = acos(f)/M_PI*180;
        return angle;
    };
    double Max(void) { //valor m�ximo entre as coordenadas
        double max;
        if (x > y) {
            max = x;
        } else {
            max = y;
        }
        if (z > max) {
            max = z;
        }
        return max;
    };
    double Min(void) { //valor minimo entre as coordenadas
        double min;
        if (x < y) {
            min = x;
        } else {
            min = y;
        }
        if (z < min) {
            min = z;
        }
        return min;
    };
    vector Abs(void) { //valor absoluto das coordenadas
        vector v;
        v.x = fabs(x);
        v.y = fabs(y);
        v.z = fabs(z);
        return v;
    };

    float modulo(){
      return sqrt(x*x+y*y+z*z);
    }

};
//---------------------------------------------------------------------------
class point {
public:
    double x,y,z;

    void init(double a,double b, double c){
        x=a;
        y=b;
        z=c;

    };
    point operator+(vector v) { //transla��o
        point p;
        p.x=x+v.x;
        p.y=y+v.y;
        p.z=z+v.z;
        return p;
    };
    point operator+(point p2) { //soma das coordenadas dos pontos
        point p1;
        p1.x=x+p2.x;
        p1.y=y+p2.y;
        p1.z=z+p2.z;
        return p1;
    };
    vector operator-(point p) { //cria��o de vetor
        vector v;
        v.x=x-p.x;
        v.y=y-p.y;
        v.z=z-p.z;
        return v;
    };
    point operator*(double f) { //multiplica��o por escalar
        point p;
        p.x=x*f;
        p.y=y*f;
        p.z=z*f;
        return p;
    };
    point operator/(double f) { //divis�o por escalar
        point p;
        p.x=x/f;
        p.y=y/f;
        p.z=z/f;
        return p;
    };
    void operator=(double f) {  //mesmo valor para x, y e z
        x=y=z=f;
    };

    bool operator==(point p) {  //igualdade entre pontos
        if(x==p.x&&y==p.y&&z==p.z)
            return 1;
        else
            return 0;
    };
    bool operator!=(point p) {  //desigualdade entre pontos
        if(x==p.x&&y==p.y&&z==p.z)
            return 0;
        else
            return 1;
    };
    double Max(void) { //valor m�ximo entre as coordenadas
        double max;
        if (x > y) {
            max = x;
        } else {
            max = y;
        }
        if (z > max) {
            max = z;
        }
        return max;
    };
    double Min(void) { //valor minimo entre as coordenadas
        double min;
        if (x < y) {
            min = x;
        } else {
            min = y;
        }
        if (z < min) {
            min = z;
        }
        return min;
    };
    point Abs(void) { //valor absoluto das coordenadas
        point v;
        v.x = fabs(x);
        v.y = fabs(y);
        v.z = fabs(z);
        return v;
    };

    double distancia (point p2) {
        return sqrt((p2.x-x)*(p2.x-x)+(p2.y-y)*(p2.y-y)+(p2.z-z)*(p2.z-z));
    };

    vector restaPuntos(point b) {
        vector v;
        v.x= x - b.x;
        v.y= y - b.y;
        v.z= z - b.z;
        return v;
    }

};
//---------------------------------------------------------------------------
class color {
public:
    double R,G,B;   //Red, Green and Blue

    color operator*(double f) { //produto escalar
        color c;
        c.R=R*f;
        c.G=G*f;
        c.B=B*f;
        return c;
    };
    void operator=(double f) {  //same value to R, G and B
        R=G=B=f;
    };
};
//---------------------------------------------------------------------------
class nuevotriangle {
public:
    point p0,p1,p2; //triangle Points
    int Projection; //projection
    double a0;      //a0 constante para c�lculos futuros
    int CID;        //JFLN:  Configuration ID

    void CalculateProjection() {
        vector n;
        double x0,y0,z0,x1,y1,z1,x2,y2,z2;
        x0=p0.x;
        y0=p0.y;
        z0=p0.z;
        x1=p1.x;
        y1=p1.y;
        z1=p1.z;
        x2=p2.x;
        y2=p2.y;
        z2=p2.z;
        n=(p1-p0)/(p2-p0);
        n.x=n.x*n.x;
        n.y=n.y*n.y;
        n.z=n.z*n.z;
        if((n.x>=n.y)&&(n.x>=n.z)) {                        //proje��o yz
            Projection=yz;
            a0=1/(-y1*z0+y2*z0+y0*z1-y2*z1-y0*z2+y1*z2 + 0.000001);
        }
        if((n.y>=n.x)&&(n.y>=n.z)) {                        //proje��o xz
            Projection=xz;
            a0=1/(-x1*z0+x2*z0+x0*z1-x2*z1-x0*z2+x1*z2 + 0.000001);
        }
        if((n.z>=n.x)&&(n.z>=n.y)) {                        //proje��o xy
            Projection=xy;
            a0=1/(-x1*y0+x2*y0+x0*y1-x2*y1-x0*y2+x1*y2 + 0.000001);
        }
    };
};
//---------------------------------------------------------------------------
class triangle {
public:
    point p0,p1,p2; //triangle Points
    int Projection; //projection
    double a0;      //a0 constante para c�lculos futuros
    //area a;

    void CalculateProjection() {
        vector n;
        double x0,y0,z0,x1,y1,z1,x2,y2,z2;
        x0=p0.x;
        y0=p0.y;
        z0=p0.z;
        x1=p1.x;
        y1=p1.y;
        z1=p1.z;
        x2=p2.x;
        y2=p2.y;
        z2=p2.z;
        n=(p1-p0)/(p2-p0);
        n.x=n.x*n.x;
        n.y=n.y*n.y;
        n.z=n.z*n.z;
        if((n.x>=n.y)&&(n.x>=n.z)) {                        //proje��o yz
            Projection=yz;
            a0=1/(-y1*z0+y2*z0+y0*z1-y2*z1-y0*z2+y1*z2 + 0.000001);
        }
        if((n.y>=n.x)&&(n.y>=n.z)) {                        //proje��o xz
            Projection=xz;
            a0=1/(-x1*z0+x2*z0+x0*z1-x2*z1-x0*z2+x1*z2 + 0.000001);
        }
        if((n.z>=n.x)&&(n.z>=n.y)) {                        //proje��o xy
            Projection=xy;
            a0=1/(-x1*y0+x2*y0+x0*y1-x2*y1-x0*y2+x1*y2 + 0.000001);
        }
    };

    double Module(vector v) { //JFLN: Returns the vector's module
        double m;
        m=sqrt(v*v);
        return m;
    }
    double TriangleArea() {
        double a;
        a=0.5*Module((p1-p0)/(p2-p0));
        return a;
    };
    

    bool rayTriangleIntersect(vector &orig, vector &dir, vector &v0, vector &v1, vector &v2, float &t){

            // compute plane's normal
            vector v0v1 = v1 - v0;
            vector v0v2 = v2 - v0;
            // no need to normalize
            vector N = v0v1/(v0v2); // N
            float area2 = N.modulo();

            // Step 1: finding P

            // check if ray and plane are parallel ?
            float NdotRayDirection = N*(dir);
            if (fabs(NdotRayDirection) < KEPSILON) // almost 0
                return false; // they are parallel so they don't intersect !

            // compute d parameter using equation 2
            float d = N*(v0);

            // compute t (equation 3)
            t = (N*(orig) + d) / NdotRayDirection;
            // check if the triangle is in behind the ray
            if (t < 0) return false; // the triangle is behind

            // compute the intersection point using equation 1
            vector P = orig + dir * t;

            // Step 2: inside-outside test
            vector C; // vector perpendicular to triangle's plane

            // edge 0
            vector edge0 = v1 - v0;
            vector vp0 = P - v0;
            C = edge0/(vp0);
            if (N*(C) < 0) return false; // P is on the right side

            // edge 1
            vector edge1 = v2 - v1;
            vector vp1 = P - v1;
            C = edge1/(vp1);
            if (N*(C) < 0)  return false; // P is on the right side

            // edge 2
            vector edge2 = v0 - v2;
            vector vp2 = P - v2;
            C = edge2/(vp2);
            if (N*(C) < 0) return false; // P is on the right side;

            return true; // this ray hits the triangle
        };

        bool operator==(triangle t) { //igualdade entre vetores
        if( p0==(t.p0) && p1==(t.p1) && p2==(t.p2) )
            return 1;
        else
            return 0;
        };

};
//---------------------------------------------------------------------------
struct ray {
    point p;                    //Point of application
    vector v;                   //orientation Vector
    double d;                   //traveled Distance
    double e[NB];               //Energy [frequency band]
};
//---------------------------------------------------------------------------
struct reflection {
    point r[MaxNPoints];                    //Points of application
    int N;                                  //JFLN: Number of reflections
    bool lost;                              //JFLN: If lost equal true, it's a reflection of a lost ray
    int Ray;                                //JFLN: Number of RAY in preview
};
//---------------------------------------------------------------------------
struct element {
    triangle    t;  //Triangle
    point       p;  //central Point
    vector      n;  //Normal
    double      A;  //Area
    int         P;  //concerned to Plane...
    int         T;  //concerned to Triangle...
};
//---------------------------------------------------------------------------
struct nuevoconfig {
    double  RayNumber,      //ray number per source
    Temperature,    //atmosphere temperature
    Humidity,       //atmosphere humidity
    Pressure,       //atmosphere pressure
    D,              //impulse response Discretization
    SurfaceD,       //surface Discretization
    StopDecay;      //stop decay
    bool     Sabine,         //stop decay formulae
    Eyring,         //stop decay formulae
    Fitzroy;        //stop decay formulae
};
//---------------------------------------------------------------------------
struct config {
    double  a,              //Alpha [horizontal viewer angle]
    b,              //Beta [vertical viewer angle]
    d,              //observer Distance
    f,              //Fov [focus angle]
    g,              //Grig space
    e;              //grid Elements
    point   c;              //Central point [blue point]
    bool    Grid;           //Grid on/off
    double  Temperature,    //atmosphere temperature
    Humidity,       //atmosphere humidity
    Pressure,       //atmosphere pressure
    D,              //impulse response Discretization
    SurfaceD,       //surface Discretization
    StopDecay;      //stop decay
    bool     Sabine,         //stop decay formulae
    Eyring,         //stop decay formulae
    Fitzroy;        //stop decay formulae
};
//---------------------------------------------------------------------------
class audience {
public:
    char        Name[MaxNChar+1];   //name
    double      Radius;             //receiver disc radius
    point       Target;             //target
    double      Rotation;           //rotation
    double      Grid;               //grid discretization
    color       Color;              //color RGB
    bool        On;                 //on?
    int         NP;                 //Number of Points
    point       p[MaxNPoints];      //Points
    int         NT;                 //Number of Triangles
    triangle    t[MaxNPoints-2];    //Triangles
    point       CentralPoint;       //central point
    vector      b0,b1,b2;           //vectorial Base

    void CalculateBase() {
        vector tb0,tb1,tb2,Up;
        double a;
        a=Rotation*PI/180;
        Up.x=0;
        Up.y=0;
        Up.z=1;
        tb0=(Target-CentralPoint)/sqrt((Target-CentralPoint)*(Target-CentralPoint));    //=Normal(Target-p)
        if((Up/tb0)*(Up/tb0)==0) {
            Up.x=1;
            Up.y=0;
            Up.z=0;
        }
        tb1=(Up/tb0)/sqrt((Up/tb0)*(Up/tb0));       //=Normal(Up/tb0)
        tb2=(tb0/tb1)/sqrt((tb0/tb1)*(tb0/tb1));    //=Normal(tb0/tb1)
        b0=tb0;
        b1=tb1*cos(a)+tb2*sin(a);
        b2=tb1*sin(-a)+tb2*cos(a);
    };

    void Clear() {
        int P,T;
        Name[0]='A';
        Name[1]='u';
        Name[2]='d';
        Name[3]='i';
        Name[4]='e';
        Name[5]='n';
        Name[6]='c';
        Name[7]='e';
        Name[8]=' ';
        Name[9]='#';
        Name[10]=NULL;
        Radius=0.15;
        Target=0;
        Rotation=0;
        Grid=200;
        Color.R=0.5;
        Color.G=1;
        Color.B=0.5;
        On=true;
        NP=0;
        for(P=0; P<MaxNPoints; P++)
            p[P]=0;
        NT=0;
        for(T=0; T<MaxNPoints-2; T++) {
            t[T].p0=0;
            t[T].p1=0;
            t[T].p2=0;
            t[T].Projection=0;
            t[T].a0=0;
        }
        CentralPoint=0;
        b0=0;
        b1=0;
        b2=0;
    };
};
//---------------------------------------------------------------------------
class reflector {
public:
    int S;                  //Source
    int P;                  //Plane
    point p[MaxNPoints];    //reflection Points

    void Clear() {
        int i;
        S=0;
        P=0;
        for(i=0; i<MaxNPoints; i++)
            p[i]=0;
    };
};
//---------------------------------------------------------------------------
class nuevomaterial {
public:
    int     serial;                 //Id Number
    char    Name[MaxNChar*6];       //name
    double  a[NB2];                 //Absorption [frequency band]
    double  s[NB2];                 //Scattering [frequency band]
    int     ca1;                    //Character of absorption
    int     ca2;                    //Character of absorption
    int     mc1;                    //Material criteria
    int     mc2;                    //Material criteria
    int     sr1;                    //Surface suitability
    int     sr2;                    //Surface suitability
    color   Color;                  //color RGB
    char    Reference[MaxNChar*2];  //reference
    void Clear() {
        int N,B;
        serial = None;
        for(N=0; N<MaxNChar*6; N++) {
            Name[0]=NULL;
        }
        for(B=0; B<NB2; B++) {
            a[B]=None;
            s[B]=None;
        }
        ca1 = None;
        ca2 = None;
        mc1 = None;
        mc2 = None;
        sr1 = None;
        sr2 = None;
        Color.R=0.5;
        Color.G=0.5;
        Color.B=1;
    };
};
//---------------------------------------------------------------------------
class material {
public:
    char    Name[MaxNChar+1];   //name
    double  a[NB];              //Absorption [frequency band]
    double  s[NB];              //Scattering [frequency band]
    double  i[NB];              //transmIssion [frequency band]
    color   Color;              //color RGB

    void Clear() {
        int B;
        Name[0]=NULL;
        for(B=0; B<NB; B++) {
            a[B]=0;
            s[B]=0;
            i[B]=0;
        }
        Color.R=0.5;
        Color.G=0.5;
        Color.B=1;
    };
};
//---------------------------------------------------------------------------
class layer {
public:
    char      Name[MaxNChar+1];
    material  Material;
    color     Color;
};
//---------------------------------------------------------------------------
class directivity {
public:
    char    Name[MaxNChar+1];   //name
    double  Spectrum[NB];       //power spectrum
    double  d[NB][MaxNAngles];  //Directivity [frequency band][azimutal angle]

    void Normalize() {
        int B,A;
        double c;
        c=0;
        for(B=0; B<NB; B++)
            c+=Spectrum[B]/NB;
        for(B=0; B<NB; B++)
            Spectrum[B]/=c;
        for(A=0; A<MaxNAngles; A++) {
            c=0;
            for(B=0; B<NB; B++)
                c+=d[B][A]/NB;
            for(B=0; B<NB; B++)
                d[B][A]/=c;
        }
    };

    void Clear() {
        Name[0]=NULL;
        for(int B=0; B<NB; B++)
            Spectrum[B]=1;
        for(int B=0; B<NB; B++)
            for(int A=0; A<MaxNAngles; A++)
                d[B][A]=1;
    };
};
//---------------------------------------------------------------------------
class rresults_new {
public:
    int     R;                              //concerned to Receiver...
    int     D;                              //impulse response Discretization
    int     StopTime[NB+1];                 //stop time[frequency band]
    float   *HybridIR[NB+1];                //HybridIR[frequency band][time]    frequency band={global,125Hz,...,4KHz}
    float   *SpecularIR[NB+1];              //SpecularIR[frequency band][time]  frequency band={global,125Hz,...,4KHz}
    float   *DiffuseIR[NB+1];               //DiffuseIR[frequency band][time]   frequency band={global,125Hz,...,4KHz}
    float   *DecayCurve[NB+1];              //DecayCurve[frequency band][time]  frequency band={global,125Hz,...,4KHz}
    int     NumQAP;                         //Number of Quality Acoustics Parameters
    float   *QltyAcouParam[NB+1];           //Quality Acoustics Parameters[frequency band][name]
    //    frequency band={global,125Hz,...,4KHz}
    //    name={T30, EDT, D50, "D80", "C50", C80, TS, G, "LG", LF, LFC, "ST1"}
    //        ={0,    1,    2,    3,    4,    5,   6, 7,  8,    9,  10,   11 }

//allocate memory for graphs
    void NewData() {
        int B,t,N;
        NumQAP=12;      //JFLN: Can be more than 12
        for(B=0; B<NB+1; B++) {
            HybridIR[B]=new float[StopTime[B]];
            SpecularIR[B]=new float[StopTime[B]];
            DiffuseIR[B]=new float[StopTime[B]];
            DecayCurve[B]=new float[StopTime[B]];
            QltyAcouParam[B]=new float[NumQAP];
        }
        //clear
        for(B=0; B<NB+1; B++) {
            for(t=0; t<StopTime[B]; t++) {
                HybridIR[B][t]=0;
                SpecularIR[B][t]=0;
                DiffuseIR[B][t]=0;
                DecayCurve[B][t]=0;
            }
            for(N=0; N<NumQAP; N++) {
                QltyAcouParam[B][N]=0;
            }
        }
    };
//clear
    void Clear() {
        int i,B;
        R=0;
        D=0;
        NumQAP=12;      //JFLN: Can be more than 12
        for(B=0; B<NB+1; B++) {
            if(StopTime[B]>0) {
                delete[] HybridIR[B];
                HybridIR[B]=NULL;
                delete[] SpecularIR[B];
                SpecularIR[B]=NULL;
                delete[] DiffuseIR[B];
                DiffuseIR[B]=NULL;
                delete[] DecayCurve[B];
                DecayCurve[B]=NULL;
            }
            StopTime[B]=0;
        }
        for(B=0; B<NB+1; B++) {
            if(NumQAP>0) {
                delete[] QltyAcouParam[B];
                QltyAcouParam[B]=NULL;
            }
            NumQAP=0;
        }
    };
//initialize
    void Init() {
        int i,B;
        R=0;
        D=0;
        NumQAP=0;
        for(B=0; B<NB+1; B++) { //JFLN: Nova estrutura considear NB+1 resultados
            HybridIR[B]=NULL;
            SpecularIR[B]=NULL;
            DiffuseIR[B]=NULL;
            DecayCurve[B]=NULL;
            StopTime[B]=0;
            QltyAcouParam[B]=NULL;

        }
    };
};
//---------------------------------------------------------------------------
class rresults {
public:
    int     R;                              //concerned to Receiver...
    int     D;                              //impulse response Discretization
    int     StopTime[NB+1];                 //stop time[frequency band]
    float   *HybridIR[NB+1];                //HybridIR[frequency band][time]    frequency band={global,125Hz,...,4KHz}
    float   *SpecularIR[NB+1];              //SpecularIR[frequency band][time]  frequency band={global,125Hz,...,4KHz}
    float   *DiffuseIR[NB+1];               //DiffuseIR[frequency band][time]   frequency band={global,125Hz,...,4KHz}
    float   *DecayCurve[NB+1];              //DecayCurve[frequency band][time]  frequency band={global,125Hz,...,4KHz}
    float   T30[NB];                        //T30 [frequency band]
    float   EDT[NB];                        //EDT [frequency band]
    float   D50[NB];                        //D50 [frequency band]
    float   C80[NB];                        //C80 [frequency band]
    float   TS[NB];                         //TS [frequency band]
    float   G[NB];                          //G [frequency band]
    float   LF[NB];                         //LF [frequency band]
    float   LFC[NB];                        //LFC [frequency band]
//allocate memory for graphs
    void NewData() {
        int B,t;
        for(B=0; B<NB+1; B++) {
            HybridIR[B]=new float[StopTime[B]];
            SpecularIR[B]=new float[StopTime[B]];
            DiffuseIR[B]=new float[StopTime[B]];
            DecayCurve[B]=new float[StopTime[B]];
        }
        //clear
        for(B=0; B<NB+1; B++)
            for(t=0; t<StopTime[B]; t++) {
                HybridIR[B][t]=0;
                SpecularIR[B][t]=0;
                DiffuseIR[B][t]=0;
                DecayCurve[B][t]=0;
            }
    };
//clear
    void Clear() {
        int i,B;
        R=0;
        D=0;
        for(B=0; B<NB+1; B++) {
            if(StopTime[B]>0) {
                delete[] HybridIR[B];
                delete[] SpecularIR[B];
                delete[] DiffuseIR[B];
                delete[] DecayCurve[B];

                HybridIR[B]=NULL;
                SpecularIR[B]=NULL;
                DiffuseIR[B]=NULL;
                DecayCurve[B]=NULL;
            }
            StopTime[B]=0;
        }
        for(B=0; B<NB; B++) {
            T30[B]=0;
            EDT[B]=0;
            D50[B]=0;
            C80[B]=0;
            TS[B]=0;
            G[B]=0;
            LF[B]=0;
            LFC[B]=0;
        }
    };
//initialize
    void Init() {
        int i,B;
        R=0;
        D=0;
        for(B=0; B<NB+1; B++) {
            HybridIR[B]=NULL;
            SpecularIR[B]=NULL;
            DiffuseIR[B]=NULL;
            DecayCurve[B]=NULL;
            StopTime[B]=0;
        }
        for(B=0; B<NB; B++) { //JFLN: Verificar o NB+1
            T30[B]=0;
            EDT[B]=0;
            D50[B]=0;
            C80[B]=0;
            TS[B]=0;
            G[B]=0;
            LF[B]=0;
            LFC[B]=0;
        }
    };
};
//---------------------------------------------------------------------------
class plane {
public:

    char        Name[MaxNChar+1];       //name
    double      a[NB];                  //Absorption [frequency band]
    double      s[NB];                  //Scattering [frequency band]
    double      i[NB];                  //transmIssion [frequency band]
    char        Material[MaxNChar+1];   //material
    color       Color;                  //color RGB
    int         NP;                     //Number of Points
    point       p[MaxNPoints];          //plane Points
    int         NT;                     //Number of Triangles
    triangle    t[MaxNPoints-2];        //plane Triangles
    vector      n;                      //Normal vector
    int         Group;                  //group
    char        Layer[MaxNChar+1];      //Layer


 /*   void NewPoints(int N) {
        int P;
        point *tp;
        tp=new point[NP+N];
        for(P=0; P<NP; P++) {
            tp[P]=p[P];
        }
        for(P=NP; P<NP+N; P++) {
            tp[P]=0;
            p[P]=0;
        }
        if(NP>0) {
            delete[] p2;
            p2=NULL;
        }
        p2=tp;
        NP+=N;
    };
 */
    void PointGenTriangle() { //Genera 2 triangulos a partir de los v�rtices de un cuadrado
        NT=NP-2;
        int i=1;
        for(int T=0; T<NT; T++){
                i--;
                t[T].p0.x = p[i].x;
                t[T].p0.y = p[i].y;
                t[T].p0.z = p[i].z;
                i++;
                if(i==NP) i=0;
                t[T].p1.x = p[i].x;
                t[T].p1.y = p[i].y;
                t[T].p1.z = p[i].z;
                i++;
                if(i==NP) i=0;
                t[T].p2.x = p[i].x;
                t[T].p2.y = p[i].y;
                t[T].p2.z = p[i].z;
                i++;
        }
    };


    void Clear() {
        int N,B,P,T;
        for(N=0; N<MaxNChar+1; N++)
            Name[N]=NULL;
        Name[0]='P';
        Name[1]='l';
        Name[2]='a';
        Name[3]='n';
        Name[4]='e';
        Name[5]=' ';
        Name[6]='#';
        //Name[7]=NULL;
        for(B=0; B<NB; B++) {
            a[B]=0.01;
            s[B]=0.01;
            i[B]=0.01;
        }
        Material[0]='M';
        Material[1]='i';
        Material[2]='r';
        Material[3]='r';
        Material[4]='o';
        Material[5]='r';
        Material[6]=NULL;
        Color.R=0.5;
        Color.G=0.5;
        Color.B=1;
        NP=0;
        for(P=0; P<MaxNPoints; P++) p[P]=0;
        NT=0;
        for(T=0; T<MaxNPoints-2; T++) {
            t[T].p0=0;
            t[T].p1=0;
            t[T].p2=0;
            t[T].Projection=0;
            t[T].a0=0;
        }
        n=0;
        Group=0;
    };
    bool IsConvex() {
        int n;
        vector u,v;
        double ang;
        for (int n=1; n<NP-1; n++) { // ficam faltando 2 pontos (primeiro e ultimo)
            u = p[n-1]-p[n];
            v = p[n+1]-p[n];
            ang = u.Angle(v);
            if(ang > 180)return false;
        }
        return true;
    }
};
//---------------------------------------------------------------------------
//JFLN: Old Class for loading older data
class plane_ant {
public:
    char        Name[MaxNChar+1];       //name
    double      a[NB];                  //Absorption [frequency band]
    double      s[NB];                  //Scattering [frequency band]
    double      i[NB];                  //transmIssion [frequency band]
    char        Material[MaxNChar+1];   //material
    color       Color;                  //color RGB
    int         NP;                     //Number of Points
    point       p[MaxNPointsAnt];       //plane Points
    int         NT;                     //Number of Triangles
    triangle    t[MaxNPointsAnt-2];     //plane Triangles
    vector      n;                      //Normal vector
    int         Group;                  //group

    void Clear() {
        int B,P,T;
        Name[0]='P';
        Name[1]='l';
        Name[2]='a';
        Name[3]='n';
        Name[4]='e';
        Name[5]=' ';
        Name[6]='#';
        Name[7]=NULL;
        for(B=0; B<NB; B++) {
            a[B]=0.01;
            s[B]=0.01;
            i[B]=0.01;
        }
        Material[0]='M';
        Material[1]='i';
        Material[2]='r';
        Material[3]='r';
        Material[4]='o';
        Material[5]='r';
        Material[6]=NULL;
        Color.R=0.5;
        Color.G=0.5;
        Color.B=1;
        NP=0;
        for(P=0; P<MaxNPointsAnt; P++) p[P]=0;
        NT=0;
        for(T=0; T<MaxNPointsAnt-2; T++) {
            t[T].p0=0;
            t[T].p1=0;
            t[T].p2=0;
            t[T].Projection=0;
            t[T].a0=0;
        }
        n=0;
        Group=0;
    };
};
//---------------------------------------------------------------------------
class nuevoplane {
public:
    char            Name[MaxNChar+1];  //Name
    int             NP;                //Number of Points
    point           p[MaxNPoints];     //plane Points
    int             NT;                //Number of Triangles
    nuevotriangle   t[MaxNPoints-2];   //Plane Triangles
    vector          n;                 //Normal vector

    void Clear() {
        int N,B,P,T;
        for(N=0; N<MaxNChar+1; N++)
            Name[N]=NULL;
        Name[0]='P';
        Name[1]='l';
        Name[2]='a';
        Name[3]='n';
        Name[4]='e';
        Name[5]=' ';
        Name[6]='#';
        NP=0;
        for(P=0; P<MaxNPoints; P++)
            p[P]=0;
        NT=0;
        for(T=0; T<MaxNPoints-2; T++) {
            t[T].p0=0;
            t[T].p1=0;
            t[T].p2=0;
            t[T].Projection=0;
            t[T].a0=0;
        }
        n=0;
    };
    bool IsConvex() {
        int n;
        vector u,v;
        double ang;
        for (int n=1; n<NP-1; n++) { // ficam faltando 2 pontos (primeiro e ultimo)
            u = p[n-1]-p[n];
            v = p[n+1]-p[n];
            ang = u.Angle(v);
            if(ang > 180)
                return false;
        }
        return true;
    }
};
//---------------------------------------------------------------------------
class planelayer { //JFLN: Plane Layer
public:
    char            Name[MaxNChar+1];  //Plane Layer Name
    int             NP; //Number of Planes
    nuevoplane      *p; //Planes
    int             MID; //Material ID

    void NewPlanes(int N) {
        int P; //Counter
        nuevoplane *tp; //Temporal Plane Array (TPA)
        tp=new nuevoplane[NP+N]; //NP+N Elements in Temporal Plane Array
        for(P=0; P<NP; P++) {
            tp[P]=p[P]; //Temporal Plane Array = to Actual Plane Array
        }
        for(P=NP; P<NP+N; P++) {
            tp[P].Clear(); //Initializing new elements in TPA
        }
        if(NP>0) {
            delete[] p; //Delete Actual Plane Array
            p=NULL;
        }
        p=tp; //Actual Plane Array points to Temporal Plane Array
        NP+=N; //Updating number of planes
    };

    void DeletePlanes(int NSelectedPlanes,int SelectedPlane[MaxNSelectedPlanes]) {
        bool Del;  //Boolean for delete verification
        int P,i,j=0; //Counters
        if(NP>0&&NSelectedPlanes>0) {
            nuevoplane *tp; //Temporal Plane Array
            tp=new nuevoplane[NP-NSelectedPlanes]; //NP-NSP Elements in Temporal Plane Array
            for(P=0; P<NP; P++) { //Check every plane for delete verification
                Del=false;
                for(i=0; i<NSelectedPlanes; i++)
                    if(P==SelectedPlane[i])
                        Del=true; //Plane was marked to be deleted
                if(!Del) {
                    tp[j]=p[P]; //Planes not marked copied in TPA
                    j++;
                }
            }
            delete[] p; //Delete Actual Plane Array
            p=tp; //Actual Plane Array points to Temporal Plane Array
            NP-=NSelectedPlanes;  //Updating number of planes
        }
    };

    void Clear() {
        int N;
        for(N=0; N<MaxNChar+1; N++)
            Name[N]=NULL; //Name array empty
        if(NP>0) {
            delete[] p; //Free memory from plane pointer
            p=NULL;
        }
        NP=0; //Number of planes = 0
        MID=None; //No material assigned
    };

    void Init() {
        int N;
        for(N=0; N<MaxNChar+1; N++)
            Name[N]=NULL; //Name array empty
        Name[0]='P'; //Name with default name
        Name[1]='.';
        Name[2]=' ';
        Name[3]='L';
        Name[4]='a';
        Name[5]='y';
        Name[6]='e';
        Name[7]='r';
        Name[8]=' ';
        Name[9]='#';
        if(NP>0) {
            delete[] p; //Free memory from plane pointer
            p=NULL;
        } else
            p=NULL; //Plane pointer points to nothing
        NP=0; //Number of planes = 0
        MID=None; //No material assigned
    };

};
//---------------------------------------------------------------------------
class source {
public:
    char    Name[MaxNChar+1];           //name
    double  NumberOfRays;               //number of rays [10^3]
    double  Power;                      //power
    double  Delay;                      //delay
    point   p;                          //Position
    point   Target;                     //target
    double  Rotation;                   //rotation
    double  VisualRadius;               //visual radius
    char    Directivity[MaxNChar+1];    //directivity name
    color   Color;                      //color RGB
    bool    On;                         //on?
    double  Spectrum[NB];               //power spectrum
    double  d[NB][MaxNAngles];          //Directivity [frequency band][azimutal angle]
    vector  b0,b1,b2;                   //vectorial Base
    char    Layer[MaxNChar+1];          // Layer

    void CalculateBase() {
        vector tb0,tb1,tb2,Up;
        double a;
        a=Rotation*PI/180;
        Up.x=0;
        Up.y=0;
        Up.z=1;
        tb0=(Target-p)/sqrt((Target-p)*(Target-p)); //=Normal(Target-p)
        if((Up/tb0)*(Up/tb0)==0) {
            Up.x=1;
            Up.y=0;
            Up.z=0;
        }
        tb1=(Up/tb0)/sqrt((Up/tb0)*(Up/tb0));       //=Normal(Up/tb0)
        tb2=(tb0/tb1)/sqrt((tb0/tb1)*(tb0/tb1));    //=Normal(tb0/tb1)
        b0=tb0;
        b1=tb1*cos(a)+tb2*sin(a);
        b2=tb1*sin(-a)+tb2*cos(a);
    };

    void Clear() {
        int B,i;
        Name[0]='S';
        Name[1]='o';
        Name[2]='u';
        Name[3]='r';
        Name[4]='c';
        Name[5]='e';
        Name[6]=' ';
        Name[7]='#';
        Name[8]=NULL;
        NumberOfRays=100;
        Power=0.01;
        Delay=0;
        p=0;
        Target=0;
        Rotation=0;
        VisualRadius=0.3;
        Directivity[0]='O';
        Directivity[1]='m';
        Directivity[2]='n';
        Directivity[3]='i';
        Directivity[4]=NULL;
        Color.R=1;
        Color.G=0.5;
        Color.B=0.5;
        On=true;
        for(B=0; B<NB; B++)
            Spectrum[B]=1;
        for(B=0; B<NB; B++)
            for(i=0; i<MaxNAngles; i++)
                d[B][i]=1;
        b0=0;
        b1=0;
        b2=0;
    };
};
//---------------------------------------------------------------------------
//JFLN: Old Class for loading older data
class source_ant {
public:
    char    Name[MaxNChar+1];           //name
    double  NumberOfRays;               //number of rays [10^3]
    double  Power;                      //power
    double  Delay;                      //delay
    point   p;                          //Position
    point   Target;                     //target
    double  Rotation;                   //rotation
    double  VisualRadius;               //visual radius
    char    Directivity[MaxNChar+1];    //directivity name
    color   Color;                      //color RGB
    bool    On;                         //on?
    double  Spectrum[NB];               //power spectrum
    double  d[NB][MaxNAngles];          //Directivity [frequency band][azimutal angle]
    vector  b0,b1,b2;                   //vectorial Base

    void CalculateBase() {
        vector tb0,tb1,tb2,Up;
        double a;
        a=Rotation*PI/180;
        Up.x=0;
        Up.y=0;
        Up.z=1;
        tb0=(Target-p)/sqrt((Target-p)*(Target-p)); //=Normal(Target-p)
        if((Up/tb0)*(Up/tb0)==0) {
            Up.x=1;
            Up.y=0;
            Up.z=0;
        }
        tb1=(Up/tb0)/sqrt((Up/tb0)*(Up/tb0));       //=Normal(Up/tb0)
        tb2=(tb0/tb1)/sqrt((tb0/tb1)*(tb0/tb1));    //=Normal(tb0/tb1)
        b0=tb0;
        b1=tb1*cos(a)+tb2*sin(a);
        b2=tb1*sin(-a)+tb2*cos(a);
    };

    void Clear() {
        int B,i;
        Name[0]='S';
        Name[1]='o';
        Name[2]='u';
        Name[3]='r';
        Name[4]='c';
        Name[5]='e';
        Name[6]=' ';
        Name[7]='#';
        Name[8]=NULL;
        NumberOfRays=100;
        Power=0.01;
        Delay=0;
        p=0;
        Target=0;
        Rotation=0;
        VisualRadius=0.3;
        Directivity[0]='O';
        Directivity[1]='m';
        Directivity[2]='n';
        Directivity[3]='i';
        Directivity[4]=NULL;
        Color.R=1;
        Color.G=0.5;
        Color.B=0.5;
        On=true;
        for(B=0; B<NB; B++)
            Spectrum[B]=1;
        for(B=0; B<NB; B++)
            for(i=0; i<MaxNAngles; i++)
                d[B][i]=1;
        b0=0;
        b1=0;
        b2=0;
    };
};
//---------------------------------------------------------------------------
class nuevosource {
public:
    char    Name[MaxNChar+1];           //name
    double  Power;                      //power
    point   p;                          //Position
    point   Target;                     //target
    double  Rotation;                   //rotation
    double  VisualRadius;               //visual radius
    int     DID;                        //directivity id
    bool    On;                         //on?
    double  Spectrum[NB];               //power spectrum
    vector  b0,b1,b2;                   //vectorial Base

    void CalculateBase() {
        vector tb0,tb1,tb2,Up; //Temporal Vectorial Base and Unitary Vector pointing Up
        double a;
        a=Rotation*PI/180; //Convert Rotation angle in radians
        Up.x=0;
        Up.y=0;
        Up.z=1; //Defines Unitary Vector pointing Up
        tb0=(Target-p)/sqrt((Target-p)*(Target-p)); //=Normal(Target-p)
        if((Up/tb0)*(Up/tb0)==0) //If Up and tb0 are paralel
            Up.x=1;
        Up.y=0;
        Up.z=0; //Up is in x direction
        tb1=(Up/tb0)/sqrt((Up/tb0)*(Up/tb0));//=Normal(Up/tb0) //tb1 ortogonal to Up and tb0
        tb2=(tb0/tb1)/sqrt((tb0/tb1)*(tb0/tb1)); //=Normal(tb0/tb1) //tb2 ortogonal to tb1 and tb0
        b0=tb0;
        b1=tb1*cos(a)+tb2*sin(a); //Aplies a rotation angle making b0 works as the axis
        b2=tb1*sin(-a)+tb2*cos(a);  //Aplies a rotation angle making b0 works as the axis
    };

    void Clear() {
        int B,i;
        Name[0]='S';
        Name[1]='o';
        Name[2]='u';
        Name[3]='r';
        Name[4]='c';
        Name[5]='e';
        Name[6]=' ';
        Name[7]='#';
        Name[8]=NULL;
        Power=0.01;
        p=0;
        Target=0;
        Rotation=0;
        VisualRadius=0.3;
        DID=None;
        On=true;
        for(B=0; B<NB; B++)
            Spectrum[B]=1;
        b0=0;
        b1=0;
        b2=0;
    };
};
//---------------------------------------------------------------------------
class sourcelayer { //JFLN: Source Layer
public:
    char            Name[MaxNChar+1];  //Source Layer Name
    int             NS; //Number of Sources
    nuevosource     *s; //Sources
    color           Color;  //color RGB
    int             TID; //Source Type ID

    void NewSource(int N) {
        int S; //Counter
        nuevosource *ts; //Temporal Source Array (TSA)
        ts=new nuevosource[NS+N];  //NS+N Elements in Temporal Source Array
        for(S=0; S<NS; S++) {
            ts[S]=s[S];  //Temporal Source Array = to Actual Source Array
        }
        for(S=NS; S<NS+N; S++) {
            ts[S].Clear();  //Initializing new elements in TSA
        }
        if(NS>0) {
            delete[] s; //Delete Actual Source Array
            s=NULL;
        }
        s=ts; //Actual Plane Source points to Temporal Source Array
        NS+=N; //Updating number of sources
    };

    void DeleteSources(int NSelectedSources,int SelectedSource[MaxNSelectedSources]) {
        bool Del;  //Boolean for delete verification
        int S,i,j=0; //Counters
        if(NS>0&&NSelectedSources>0) {
            nuevosource *ts; //Temporal Plane Array
            ts=new nuevosource[NS-NSelectedSources]; //NS-NSS Elements in Temporal Source Array
            for(S=0; S<NS; S++) { //Check every source for delete verification
                Del=false;
                for(i=0; i<NSelectedSources; i++)
                    if(S==SelectedSource[i])
                        Del=true; //Source was marked to be deleted
                if(!Del) {
                    ts[j]=s[S]; //Sources not marked are copied in TPA
                    j++;
                }
            }
            delete[] s; //Delete Actual Source Array
            s=ts; //Actual Source Array points to Temporal Source Array
            NS-=NSelectedSources;  //Updating number of source
        }
    };

    void Clear() {
        int N;
        for(N=0; N<MaxNChar+1; N++)
            Name[N]=NULL; //Name array empty
        if(NS>0) {
            delete[] s; //Free memory from plane pointer
            s=NULL;
        }
        NS=0; //Number of planes = 0
        Color.R=1;
        Color.G=0.5;
        Color.B=0.5;
        TID=None; //No material assigned
    };

    void Init() {
        int N;
        for(N=0; N<MaxNChar+1; N++)
            Name[N]=NULL; //Name array empty
        Name[0]='S'; //SourceLayerName with default name
        Name[1]='.';
        Name[2]=' ';
        Name[3]='L';
        Name[4]='a';
        Name[5]='y';
        Name[6]='e';
        Name[7]='r';
        Name[8]=' ';
        Name[9]='#';
        if(NS>0) {
            delete[] s; //Free memory from source pointer
            s=NULL;
        } else
            s=NULL; //Source pointer points to nothing
        NS=0; //Number of sources = 0
        Color.R=1;
        Color.G=0.5;
        Color.B=0.5;
        TID=None; //No source type assigned
    };

};
//---------------------------------------------------------------------------
class receiver {
public:
    char    Name[MaxNChar+1];   //name
    double  Radius;             //receiver disc radius
    point   p;                  //Position
    point   Target;             //target
    double  Rotation;           //rotation
    double  VisualRadius;       //visual radius
    color   Color;              //color RGB
    bool    On;                 //on?
    vector  b0,b1,b2;           //vectorial Base
    char    Layer[MaxNChar+1];          // Layer

    void CalculateBase() {
        vector tb0,tb1,tb2,Up;
        double a;
        a=Rotation*PI/180;
        Up.x=0;
        Up.y=0;
        Up.z=1;
        tb0=(Target-p)/sqrt((Target-p)*(Target-p)); //=Normal(Target-p)
        if((Up/tb0)*(Up/tb0)==0) {
            Up.x=1;
            Up.y=0;
            Up.z=0;
        }
        tb1=(Up/tb0)/sqrt((Up/tb0)*(Up/tb0));       //=Normal(Up/tb0)
        tb2=(tb0/tb1)/sqrt((tb0/tb1)*(tb0/tb1));    //=Normal(tb0/tb1)
        b0=tb0;
        b1=tb1*cos(a)+tb2*sin(a);
        b2=tb1*sin(-a)+tb2*cos(a);
    };

    void Clear() {
        Name[0]='M';
        Name[1]='i';
        Name[2]='c';
        Name[3]='r';
        Name[4]='o';
        Name[5]='p';
        Name[6]='h';
        Name[7]='o';
        Name[8]='n';
        Name[9]='e';
        Name[10]=' ';
        Name[11]='#';
        Name[12]=NULL;
        Radius=0.15;
        p=0;
        Target=0;
        Rotation=0;
        VisualRadius=0.3;
        Color.R=0.5;
        Color.G=1;
        Color.B=0.5;
        On=true;
        b0=0;
        b1=0;
        b2=0;
    };
};
//---------------------------------------------------------------------------
//JFLN: Old Class for loading older data
class receiver_ant {
public:
    char    Name[MaxNChar+1];   //name
    double  Radius;             //receiver disc radius
    point   p;                  //Position
    point   Target;             //target
    double  Rotation;           //rotation
    double  VisualRadius;       //visual radius
    color   Color;              //color RGB
    bool    On;                 //on?
    vector  b0,b1,b2;           //vectorial Base

    void CalculateBase() {
        vector tb0,tb1,tb2,Up;
        double a;
        a=Rotation*PI/180;
        Up.x=0;
        Up.y=0;
        Up.z=1;
        tb0=(Target-p)/sqrt((Target-p)*(Target-p)); //=Normal(Target-p)
        if((Up/tb0)*(Up/tb0)==0) {
            Up.x=1;
            Up.y=0;
            Up.z=0;
        }
        tb1=(Up/tb0)/sqrt((Up/tb0)*(Up/tb0));       //=Normal(Up/tb0)
        tb2=(tb0/tb1)/sqrt((tb0/tb1)*(tb0/tb1));    //=Normal(tb0/tb1)
        b0=tb0;
        b1=tb1*cos(a)+tb2*sin(a);
        b2=tb1*sin(-a)+tb2*cos(a);
    };

    void Clear() {
        Name[0]='M';
        Name[1]='i';
        Name[2]='c';
        Name[3]='r';
        Name[4]='o';
        Name[5]='p';
        Name[6]='h';
        Name[7]='o';
        Name[8]='n';
        Name[9]='e';
        Name[10]=' ';
        Name[11]='#';
        Name[12]=NULL;
        Radius=0.15;
        p=0;
        Target=0;
        Rotation=0;
        VisualRadius=0.3;
        Color.R=0.5;
        Color.G=1;
        Color.B=0.5;
        On=true;
        b0=0;
        b1=0;
        b2=0;
    };
};
//---------------------------------------------------------------------------
class nuevoreceiver {
public:
    char    Name[MaxNChar+1];   //name
    double  Radius;             //receiver disc radius
    point   p;                  //Position
    point   Target;             //target
    double  Rotation;           //rotation
    double  VisualRadius;       //visual radius
    color   Color;              //color RGB
    bool    On;                 //on?
    vector  b0,b1,b2;           //vectorial Base

    void CalculateBase() {
        vector tb0,tb1,tb2,Up; //Temporal Vectorial Base and Unitary Vector pointing Up
        double a;
        a=Rotation*PI/180; //Convert Rotation angle in radians
        Up.x=0;
        Up.y=0;
        Up.z=1; //Defines Unitary Vector pointing Up
        tb0=(Target-p)/sqrt((Target-p)*(Target-p)); //=Normal(Target-p)
        if((Up/tb0)*(Up/tb0)==0) //If Up and tb0 are paralel
            Up.x=1;
        Up.y=0;
        Up.z=0; //Up is in x direction
        tb1=(Up/tb0)/sqrt((Up/tb0)*(Up/tb0));//=Normal(Up/tb0) //tb1 ortogonal to Up and tb0
        tb2=(tb0/tb1)/sqrt((tb0/tb1)*(tb0/tb1)); //=Normal(tb0/tb1) //tb2 ortogonal to tb1 and tb0
        b0=tb0;
        b1=tb1*cos(a)+tb2*sin(a); //Aplies a rotation angle making b0 works as the axis
        b2=tb1*sin(-a)+tb2*cos(a);  //Aplies a rotation angle making b0 works as the axis
    };

    void Clear() {
        Name[0]='M';
        Name[1]='i';
        Name[2]='c';
        Name[3]='r';
        Name[4]='o';
        Name[5]='p';
        Name[6]='h';
        Name[7]='o';
        Name[8]='n';
        Name[9]='e';
        Name[10]=' ';
        Name[11]='#';
        Name[12]=NULL;
        Radius=0.15;
        p=0;
        Target=0;
        Rotation=0;
        VisualRadius=0.3;
        Color.R=0.5;
        Color.G=1;
        Color.B=0.5;
        On=true;
        b0=0;
        b1=0;
        b2=0;
    };
};
//---------------------------------------------------------------------------
class receiverlayer { //JFLN: Receiver Layer
public:
    char            Name[MaxNChar+1]; //Receiver Layer Name
    int             NR; //Number of Receivers
    nuevoreceiver        *r; //Receivers

    void NewReceiver(int N) {
        int R; //Counter
        nuevoreceiver *tr; //Temporal Receiver Array (TRA)
        tr=new nuevoreceiver[NR+N];  //NR+N Elements in Temporal Receiver Array
        for(R=0; R<NR; R++) {
            tr[R]=r[R];  //Temporal Receiver Array = to Actual Receiver Array
        }
        for(R=NR; R<NR+N; R++) {
            tr[R].Clear();  //Initializing new elements in TRA
        }
        if(NR>0) {
            delete[] r; //Delete Actual Receiver Array
            r=NULL;
        }
        r=tr; //Actual Plane Receiver points to Temporal Receiver Array
        NR+=N; //Updating number of receivers
    };



    void DeleteReceivers(int NSelectedReceivers,int SelectedReceiver[MaxNSelectedReceivers]) {
        bool Del;  //Boolean for delete verification
        int R,i,j=0; //Counters
        if(NR>0&&NSelectedReceivers>0) {
            nuevoreceiver *tr; //Temporal Receiver Array
            tr=new nuevoreceiver[NR-NSelectedReceivers]; //NS-NSS Elements in Temporal Receiver Array
            for(R=0; R<NR; R++) { //Check every receiver for delete verification
                Del=false;
                for(i=0; i<NSelectedReceivers; i++)
                    if(R==SelectedReceiver[i])
                        Del=true; //Receiver was marked to be deleted
                if(!Del) {
                    tr[j]=r[R]; //Receivers not marked are copied in TPA
                    j++;
                }
            }
            delete[] r; //Delete Actual Receiver Array
            r=tr; //Actual Receiver Array points to Temporal Receiver Array
            NR-=NSelectedReceivers;  //Updating number of receivers
        }
    };

    void Clear() {
        int N;
        for(N=0; N<MaxNChar+1; N++)
            Name[N]=NULL; //Name array empty
        if(NR>0) {
            delete[] r; //Free memory from receiver pointer
            r=NULL;
        }
        NR=0; //Number of receiver = 0
    };

    void Init() {
        int N;
        for(N=0; N<MaxNChar+1; N++)
            Name[N]=NULL; //Name array empty
        Name[0]='R'; //ReceiverLayerName with default name
        Name[1]='.';
        Name[2]=' ';
        Name[3]='L';
        Name[4]='a';
        Name[5]='y';
        Name[6]='e';
        Name[7]='r';
        Name[8]=' ';
        Name[9]='#';
        if(NR>0) {
            delete[] r; //Free memory from receiver pointer
            r=NULL;
        } else
            r=NULL; //Receiver pointer points to nothing
        NR=0; //Number of receivers = 0
    };
};
//---------------------------------------------------------------------------
class nuevoroom {   //JFLN: Room Class
public:
    int             NPL;    //Number of Plane Layers
    planelayer      *pl;    //Plane Layers
    int             NSL;    //Number of Sources
    sourcelayer     *sl;    //Sources
    int             NRL;    //Number of Receiver Layers
    receiverlayer	*rl;    //Receiver Layers
    int				NRF;    //Number of reFlectors
    reflector		*rf;    //reFlector (used to see the first reflection)
    double          a,      //Alpha [horizontal viewer angle]
    b,      //Beta [vertical viewer angle]
    d,      //observer Distance
    f,      //Fov [focus angle]
    g,      //Grig space
    e;      //grid Elements
    point           c;      //Central point [blue point]
    bool            Grid;   //Grid on/off

    void NewPlaneLayer(int N) {
        int PL; //Counter
        planelayer *tpl; //Temporal Plane Layer
        tpl=new planelayer[NPL+N]; //NPL+N Temporal Plane Layers
        for(PL=0; PL<NPL; PL++) {
            tpl[PL]=pl[PL]; //NPL Temporal Plane Layers = NPL Actual Plane Layers
        }
        for(PL=NPL; PL<NPL+N; PL++) {
            tpl[PL].Init(); //Initializing New Plane Layers
        }
        if(NPL>0) {
            delete[] pl; //Delete Actual Plane Layers
            pl=NULL;
        }
        pl=tpl; //Make Temporal Plane Layers be the Actual Plane Layers
        NPL+=N; //Updating de Number of Plane Layers
    };

    void NewSourceLayer(int N) {
        int SL; //Counter
        sourcelayer *tsl; //Temporal Source Layer
        tsl=new sourcelayer[NSL+N]; //NSL+N Temporal Source Layers
        for(SL=0; SL<NSL; SL++) {
            tsl[SL]=sl[SL]; //NSL Temporal Source Layers = NSL Actual Source Layers
        }
        for(SL=NSL; SL<NSL+N; SL++) {
            tsl[SL].Init(); //Initializing New Source Layers
        }
        if(NSL>0) {
            delete[] sl; //Delete Actual Source Layers
            sl=NULL;
        }
        sl=tsl; //Make Temporal Source Layers be the Actual Source Layers
        NSL+=N; //Updating de Number of Source Layers
    };

    void NewReceiverLayer(int N) {
        int RL; //Counter
        receiverlayer *trl; //Temporal Receiver Layer
        trl=new receiverlayer[NRL+N]; //NRL+N Temporal Receiver Layers
        for(RL=0; RL<NRL; RL++) {
            trl[RL]=rl[RL]; //NRL Temporal Receiver Layers = NRL Actual Receiver Layers
        }
        for(RL=NRL; RL<NRL+N; RL++) {
            trl[RL].Init(); //Initializing New Receiver Layers
        }
        if(NRL>0) {
            delete[] rl; //Delete Actual Receiver Layers
            rl=NULL;
        }
        rl=trl; //Make Temporal Receiver Layers be the Actual Receiver Layers
        NRL+=N; //Updating de Number of Receiver Layers
    };

    void NewReflector(int N) {
        int RF; //Counter
        reflector *trf; //Temporal Reflector
        trf=new reflector[NRF+N]; //NF+N Temporal Reflectors
        for(RF=0; RF<NRF; RF++)
            trf[RF]=rf[RF];   //NF Temporal Reflectors = NF Actual Reflectors
        for(RF=NRF; RF<NRF+N; RF++)
            trf[RF].Clear();
        if(NRF>0)
            delete[] rf;
        rf=trf;
        NRF+=N;
    };

    void DeletePlaneLayer(int PL) {
        if(NPL>0&&PL>0) {
            int i,j=0;
            planelayer *tpl;
            tpl=new planelayer[NPL-1];
            for(i=0; i<NPL; i++)
                if(i!=PL) {
                    tpl[j]=pl[i];
                    j++;
                }
            pl[PL].Clear();
            delete[] pl;
            pl=tpl;
            NPL--;
        }
    };

    void DeleteSourceLayer(int SL) {
        if(NSL>0&&SL>None) {
            int i,j=0;
            sourcelayer *tsl;
            tsl=new sourcelayer[NSL-1];
            for(i=0; i<NSL; i++)
                if(i!=SL) {
                    tsl[j]=sl[i];
                    j++;
                }
            delete[] sl;
            sl=tsl;
            NSL--;
        }
    };

    void DeleteReceiver(int RL) {
        if(NRL>0&&RL>None) {
            int i,j=0;
            receiverlayer *trl;
            trl=new receiverlayer[NRL-1];
            for(i=0; i<NRL; i++)
                if(i!=RL) {
                    trl[j]=rl[i];
                    j++;
                }
            delete[] rl;
            rl=trl;
            NRL--;
        }
    };

    void DeleteReflector(int R) {
        if(NRF>0&&R>None) {
            int i,j=0;
            reflector *trf;
            trf=new reflector[NRF-1];
            for(i=0; i<NRF; i++)
                if(i!=R) {
                    trf[j]=rf[i];
                    j++;
                }
            delete[] rf;
            rf=trf;
            NRF--;
        }
    };

    void Clear() {
        if(NPL>0) {
            delete[] pl;
            pl=NULL;
        }
        NPL=0;
        if(NSL>0) {
            delete[] sl;
            sl=NULL;
        }
        NSL=0;
        if(NRL>0) {
            delete[] rl;
            rl=NULL;
        }
        NRL=0;
        a   =19*PI/60;
        b   =13*PI/60;
        d   =30;
        f   =0.5;      //approximately 30 degrees (or PI*30/180 rad)
        g   =0.2;
        e   =40;
        c   =0;
        Grid=true;
    };

    void Init() {
        NPL=0;
        pl=NULL;
        NSL=0;
        sl=NULL;
        NRL=0;
        rl=NULL;
        a   =19*PI/60;
        b   =13*PI/60;
        d   =30;
        f   =0.5;      //approximately 30 degrees (or PI*30/180 rad)
        g   =0.2;
        e   =40;
        c   =0;
        Grid=true;
    };
};

//---------------------------------------------------------------------------

class Ray{

        public:
        vector origin;
        vector direction;
        vector inv_direction;
        int sign[3];

        Ray(){};
        Ray(vector o, vector d) {
                origin = o;
                direction = d;
                inv_direction.x=1.0/d.x;
                inv_direction.y=1.0/d.y;
                inv_direction.z=1.0/d.z;
                sign[0] = (inv_direction.x < 0);
                sign[1] = (inv_direction.y < 0);
                sign[2] = (inv_direction.z < 0);
        }

        Ray(const Ray &r) {
                origin = r.origin;
                direction = r.direction;
                inv_direction = r.inv_direction;
                sign[0] = r.sign[0]; sign[1] = r.sign[1]; sign[2] = r.sign[2];
        }
        double Module(vector v) { //JFLN: Returns the vector's module
                double m;
                m=sqrt(v*v);
        return m;
        };

        vector Normal(vector v1) { //JFLN: Returns the vector's unitary vector
                                        //compare with the function unitario because this funtion is the same in MathFuntions
                                double m;
                                vector v2;
                                m=Module(v1);
                                if(m==0)
                                v2=0;
                                else
                                v2=v1/m;
                                return v2;
        };
};

//---------------------------------------------------------------------------

class Box {
  public:
    point vertexs[2];
    Box() { }
    Box(const point &min, const point &max) {
      vertexs[0] = min;
      vertexs[1] = max;
    }
};

//---------------------------------------------------------------------------

class Octree {
public:
    //Elementos miembro
    point m_vCenter;
    triangle* nodeTriangles;
    float m_Width;
    int *g_CurrentSubdivision;
    bool m_bSubDivided;
    Octree *m_pOctreeNodes[8];
    int *g_EndNodeCount;
    int m_TriangleCount;
    point vertexs[2];


    //Constructor
    Octree() {
        //Init pointers and variables
        m_vCenter=0;
        nodeTriangles=NULL;
        m_Width=0;
        g_CurrentSubdivision=NULL;
        m_bSubDivided=false;
        for(int i=0;i<8;i++)
                m_pOctreeNodes[i]=NULL;
    }

    //Destructor
    ~Octree() {
        //Free allocated memory
        delete[] nodeTriangles;
        nodeTriangles=NULL;
    }

    // These values (0 - 7) store the index ID's for the octree node array (m_pOctreeNodes)
    enum eOctreeNodes {
        TOP_LEFT_FRONT,			// 0
        TOP_LEFT_BACK,			// 1
        TOP_RIGHT_BACK,			// etc...
        TOP_RIGHT_FRONT,
        BOTTOM_LEFT_FRONT,
        BOTTOM_LEFT_BACK,
        BOTTOM_RIGHT_BACK,
        BOTTOM_RIGHT_FRONT
    };

    // This sets the initial width, height and depth for the whole scene
    void GetSceneDimensions(triangle *roomTriangles, int numberOfTriangles) {
        // We pass in the list of triangles and the triangle count to get the
        // center point and width of the whole scene.  We use this information
        // to subdivide our octree.
        // Initialize some temporary variables to hold the max dimensions found
        float maxWidth = 0, maxHeight = 0, maxDepth = 0;
        // Return from this function if we passed in bad data
        if(!roomTriangles || numberOfTriangles <= 0) return;

        // Below we calculate the center point of the scene.  To do this, all you
        // need to do is add up ALL the vertices, then divide that total by the
        // number of vertices added up.  So all the X's get added up together, then Y's, etc..
        // This doesn't mean in a single number, but 3 separate floats (totalX, totalY, totalZ).
        // Notice that we are adding 2 vectors together.  If you look in the CVector3 class
        // I overloaded the + and - operator to handle it correctly.  It cuts down on code
        // instead of added the x, then the y, then the z separately.  If you don't want
        // to use operator overloading just make a function called CVector AddVector(), etc...
        // Go through all of the vertices and add them up to eventually find the center

        //Establesing points maximum and minimum for calculate of center room

        double maxX=0, maxY=0, maxZ=0, minX=0, minY=0, minZ=0;

        //For once triangle calculate of cartesian coord in x in y in z

        for(int i=0; i<numberOfTriangles; i++) {

            if(maxX < roomTriangles[i].p0.x) maxX=roomTriangles[i].p0.x;
            if(minX > roomTriangles[i].p0.x) minX=roomTriangles[i].p0.x;
            if(maxX < roomTriangles[i].p1.x) maxX=roomTriangles[i].p1.x;
            if(minX > roomTriangles[i].p1.x) minX=roomTriangles[i].p1.x;
            if(maxX < roomTriangles[i].p2.x) maxX=roomTriangles[i].p2.x;
            if(minX > roomTriangles[i].p2.x) minX=roomTriangles[i].p2.x;

            if(maxY < roomTriangles[i].p0.y) maxY=roomTriangles[i].p0.y;
            if(minY > roomTriangles[i].p0.y) minY=roomTriangles[i].p0.y;
            if(maxY < roomTriangles[i].p1.y) maxY=roomTriangles[i].p1.y;
            if(minY > roomTriangles[i].p1.y) minY=roomTriangles[i].p1.y;
            if(maxY < roomTriangles[i].p2.y) maxY=roomTriangles[i].p2.y;
            if(minY > roomTriangles[i].p2.y) minY=roomTriangles[i].p2.y;

            if(maxZ < roomTriangles[i].p0.z) maxZ=roomTriangles[i].p0.z;
            if(minZ > roomTriangles[i].p0.z) minZ=roomTriangles[i].p0.z;
            if(maxZ < roomTriangles[i].p1.z) maxZ=roomTriangles[i].p1.z;
            if(minZ > roomTriangles[i].p1.z) minZ=roomTriangles[i].p1.z;
            if(maxZ < roomTriangles[i].p2.z) maxZ=roomTriangles[i].p2.z;
            if(minZ > roomTriangles[i].p2.z) minZ=roomTriangles[i].p2.z;
        }

        //Calculate cartesian coord of point center room
        m_vCenter.x = (maxX+minX)/2.0f;
        m_vCenter.y = (maxY+minY)/2.0f;
        m_vCenter.z = (maxZ+minZ)/2.0f;


        //With the cartesian coord establesh the width height and deph of cubo thath on room
        maxWidth=fabs(maxX)+fabs(minX);
        maxHeight=fabs(maxZ)+fabs(minZ);
        maxDepth=fabs(maxY)+fabs(minY);

        // Check if the width is the highest value and assign that for the cube dimension
        if(maxWidth > maxHeight && maxWidth > maxDepth)
            m_Width = maxWidth;

        // Check if the height is the heighest value and assign that for the cube dimension
        else if(maxHeight > maxWidth && maxHeight > maxDepth)
            m_Width = maxHeight;

        // Else it must be the depth or it's the same value as some of the other ones
        else
            m_Width = maxDepth;


    }

    int getPointNode(point vPoint,point vCenter) {
        point vCtr = vCenter;

        // Check if the point lines within the TOP LEFT FRONT node
        if( (vPoint.x <= vCtr.x) && (vPoint.y >= vCtr.y) && (vPoint.z >= vCtr.z) )
            return TOP_LEFT_FRONT;

        // Check if the point lines within the TOP LEFT BACK node
        if( (vPoint.x <= vCtr.x) && (vPoint.y >= vCtr.y) && (vPoint.z <= vCtr.z) )
            return TOP_LEFT_BACK;

        // Check if the point lines within the TOP RIGHT BACK node
        if( (vPoint.x >= vCtr.x) && (vPoint.y >= vCtr.y) && (vPoint.z <= vCtr.z) )
            return TOP_RIGHT_BACK;

        // Check if the point lines within the TOP RIGHT FRONT node
        if( (vPoint.x >= vCtr.x) && (vPoint.y >= vCtr.y) && (vPoint.z >= vCtr.z) )
            return TOP_RIGHT_FRONT;

        // Check if the point lines within the BOTTOM LEFT FRONT node
        if( (vPoint.x <= vCtr.x) && (vPoint.y <= vCtr.y) && (vPoint.z >= vCtr.z) )
            return BOTTOM_LEFT_FRONT;

        // Check if the point lines within the BOTTOM LEFT BACK node
        if( (vPoint.x <= vCtr.x) && (vPoint.y <= vCtr.y) && (vPoint.z <= vCtr.z) )
            return BOTTOM_LEFT_BACK;

        // Check if the point lines within the BOTTOM RIGHT BACK node
        if( (vPoint.x >= vCtr.x) && (vPoint.y <= vCtr.y) && (vPoint.z <= vCtr.z) )
            return BOTTOM_RIGHT_BACK;

        // Check if the point lines within the BOTTOM RIGHT FRONT node
        if( (vPoint.x >= vCtr.x) && (vPoint.y <= vCtr.y) && (vPoint.z >= vCtr.z) )
            return BOTTOM_RIGHT_FRONT;
        return -1;
    }

    void CreateNewNode(std::vector<triangle> triList, point vCenter, float width, int nodeID){
	// This function helps us set up the new node that is being created.  We only
	// want to create a new node if it found triangles in it's area.  If there were
	// no triangle found in this node's cube, then we ignore it and don't create a node.
        // Check if the first node found some triangles in it
	if(triList.size())
	{
		// Create an counter to count the current index of the new node vertices

                triangle *m_pTriangles = new triangle [triList.size()];

		// Go through all the vertices and assign the vertices to the node's list
		for(int i = 0; i < triList.size(); i++){
			m_pTriangles[i] = triList[i];
		}

		// Now comes the initialization of the node.  First we allocate memory for
		// our node and then get it's center point.  Depending on the nodeID,
		// GetNewNodeCenter() knows which center point to pass back (TOP_LEFT_FRONT, etc..)

		// Allocate a new node for this octree
		m_pOctreeNodes[nodeID] = new Octree;

                //pasa contadores que est�n fuera de la clase octree
                m_pOctreeNodes[nodeID]->g_CurrentSubdivision=g_CurrentSubdivision;
                m_pOctreeNodes[nodeID]->g_EndNodeCount=g_EndNodeCount;

		// Get the new node's center point depending on the nodexIndex (which of the 8 subdivided cubes).
                point vNodeCenter = GetNewNodeCenter(vCenter, width, nodeID);

		// Below, before and after we recurse further down into the tree, we keep track
		// of the level of subdivision that we are in.  This way we can restrict it.

		//*g_CurrentSubdivision++;
        *g_CurrentSubdivision=*g_CurrentSubdivision+1;

        // Recurse through this node and subdivide it if necessary
        m_pOctreeNodes[nodeID]->createNode(m_pTriangles, triList.size(), vNodeCenter, width / 2);

        // Decrease the current level of subdivision
        *g_CurrentSubdivision=*g_CurrentSubdivision-1;


        //*g_CurrentSubdivision--;

	}
}

point GetNewNodeCenter(point vCenter, float width, int nodeID)
{
	// I created this function which takes an enum ID to see which node's center
	// we need to calculate.  Once we find that we need to subdivide a node we find
	// the centers of each of the 8 new nodes.  This is what that function does.
	// We just tell it which node we want.
	// Initialize the new node center
    point vNodeCenter;

	// Create a dummy variable to cut down the code size
    point vCtr = vCenter;

	// Switch on the ID to see which subdivided node we are finding the center
	switch(nodeID)
	{
		case TOP_LEFT_FRONT:
			// Calculate the center of this new node
            vNodeCenter.init(vCtr.x - width/4, vCtr.y + width/4, vCtr.z + width/4);
			break;

		case TOP_LEFT_BACK:
			// Calculate the center of this new node
            vNodeCenter.init(vCtr.x - width/4, vCtr.y + width/4, vCtr.z - width/4);
			break;

		case TOP_RIGHT_BACK:
			// Calculate the center of this new node
            vNodeCenter.init(vCtr.x + width/4, vCtr.y + width/4, vCtr.z - width/4);
			break;

		case TOP_RIGHT_FRONT:
			// Calculate the center of this new node
            vNodeCenter.init(vCtr.x + width/4, vCtr.y + width/4, vCtr.z + width/4);
			break;

		case BOTTOM_LEFT_FRONT:
			// Calculate the center of this new node
            vNodeCenter.init(vCtr.x - width/4, vCtr.y - width/4, vCtr.z + width/4);
			break;

		case BOTTOM_LEFT_BACK:
			// Calculate the center of this new node
            vNodeCenter.init(vCtr.x - width/4, vCtr.y - width/4, vCtr.z - width/4);
			break;

		case BOTTOM_RIGHT_BACK:
			// Calculate the center of this new node
            vNodeCenter.init(vCtr.x + width/4, vCtr.y - width/4, vCtr.z - width/4);
			break;

		case BOTTOM_RIGHT_FRONT:
			// Calculate the center of this new node
            vNodeCenter.init(vCtr.x + width/4, vCtr.y - width/4, vCtr.z + width/4);
			break;
	}

	// Return the new node center
	return vNodeCenter;
}

void createNode(triangle *triangles, int numberOfTriangles, point vCenter, float width) {
        // This is our main function that creates the octree.  We will recurse through
        // this function until we finish subdividing.  Either this will be because we
        // subdivided too many levels or we divided all of the triangles up.
        // Create a variable to hold the number of triangles
        //int numberOfTriangles = numberOfVerts / 3;
        // Initialize this node's center point.  Now we know the center of this node.
        m_vCenter = vCenter;
        // Initialize this nodes cube width.  Now we know the width of this current node.
        m_Width = width;

        //cONSTRUCT AXIS ALIGNED BOUNDING BOX FOR COLLISION TEST
        //setBox();

        // Check if we have too many triangles in this node and we haven't subdivided
        // above our max subdivisions.  If so, then we need to break this node into
        // 8 more nodes (hence the word OCTree).  Both must be true to divide this node.
        if( (numberOfTriangles > g_MaxTriangles) && ( *g_CurrentSubdivision < g_MaxSubdivisions) ) {
            // Since we need to subdivide more we set the divided flag to true.
            // This let's us know that this node does NOT have any vertices assigned to it,
            // but nodes that perhaps have vertices stored in them (Or their nodes, etc....)
            // We will querey this variable when we are drawing the octree.
            m_bSubDivided = true;

            // Create a list for each new node to store if a triangle should be stored in it's
            // triangle list.  For each index it will be a true or false to tell us if that triangle
            // is in the cube of that node.  Below we check every point to see where it's
            // position is from the center (I.E. if it's above the center, to the left and
            // back it's the TOP_LEFT_BACK node).  Depending on the node we set the pList
            // index to true.  This will tell us later which triangles go to which node.
            // You might catch that this way will produce doubles in some nodes.  Some
            // triangles will intersect more than 1 node right?  We won't split the triangles
            // in this tutorial just to keep it simple, but the next tutorial we will.

            std::vector<triangle> pList[8];
            std::vector<triangle> actualNodeTriangles;


            point vCtr = vCenter;

            vertexs[0].x=m_vCenter.x+(m_Width/2.0f);
            vertexs[0].y=m_vCenter.y+(m_Width/2.0f);
            vertexs[0].z=m_vCenter.z+(m_Width/2.0f);

            vertexs[1].x=m_vCenter.x-(m_Width/2.0f);
            vertexs[1].y=m_vCenter.y-(m_Width/2.0f);
            vertexs[1].z=m_vCenter.z-(m_Width/2.0f);



            // Go through all of the vertices and check which node they belong too.  The way
            // we do this is use the center of our current node and check where the point
            // lies in relationship to the center.  For instance, if the point is
            // above, left and back from the center point it's the TOP_LEFT_BACK node.
            // You'll see we divide by 3 because there are 3 points in a triangle.
            // If the vertex index 0 and 1 are in a node, 0 / 3 and 1 / 3 is 0 so it will
            // just set the 0'th index to TRUE twice, which doesn't hurt anything.  When
            // we get to the 3rd vertex index of pVertices[] it will then be checking the
            // 1st index of the pList*[] array.  We do this because we want a list of the
            // triangles in the node, not the vertices.

            int pointNodes[3]= {-1,-1,-1};

            for(int i = 0; i < numberOfTriangles; i++) {
                triangle aux=triangles[i];

                //Obtener el cuadrante de cada v?rtice del tri?ngulo
                //for(int j = 0; j < 3; j++){//recorre tres v?rtices
                pointNodes[0]=getPointNode(triangles[i].p0,vCenter);
                pointNodes[1]=getPointNode(triangles[i].p1,vCenter);
                pointNodes[2]=getPointNode(triangles[i].p2,vCenter);
                //}

                if(pointNodes[0]==pointNodes[1] && pointNodes[1]==pointNodes[2]) {
                //Revisa si los tres v?rtices est?n en un mismo nodo
                //Si lo est? lo agrega a la lista con el ?ndice del nodo hijo
                    pList[pointNodes[0]].push_back(triangles[i]);
                } else { //caso contrario
                    // dejar triangulo en la lista del nodo padre
                    actualNodeTriangles.push_back(triangles[i]);
                }

            }

            		AssignVerticesToNode(actualNodeTriangles);

            		// Next we do the dirty work.  We need to set up the new nodes with the triangles
            		// that are assigned to each node, along with the new center point of the node.
            		// Through recursion we subdivide this node into 8 more nodes.
            		// Create the subdivided nodes if necessary and then recurse through them.
            		// The information passed into CreateNewNode() are essential for creating the
            		// new nodes.  We pass the 8 ID's in so it knows how to calculate it's new center.

            		CreateNewNode(pList[TOP_LEFT_FRONT], vCenter, width,TOP_LEFT_FRONT);
            		CreateNewNode(pList[TOP_LEFT_BACK], vCenter, width, TOP_LEFT_BACK);
            		CreateNewNode(pList[TOP_RIGHT_BACK], vCenter, width, TOP_RIGHT_BACK);
            		CreateNewNode(pList[TOP_RIGHT_FRONT], vCenter, width, TOP_RIGHT_FRONT);
            		CreateNewNode(pList[BOTTOM_LEFT_FRONT], vCenter, width, BOTTOM_LEFT_FRONT);
            		CreateNewNode(pList[BOTTOM_LEFT_BACK], vCenter, width, BOTTOM_LEFT_BACK);
            		CreateNewNode(pList[BOTTOM_RIGHT_BACK], vCenter, width, BOTTOM_RIGHT_BACK);
            		CreateNewNode(pList[BOTTOM_RIGHT_FRONT], vCenter, width, BOTTOM_RIGHT_FRONT);
        } else {
            // If we get here we must either be subdivided past our max level, or our triangle
            // count went below the minimum amount of triangles so we need to store them.

            // Assign the vertices to this node since we reached the end node.
            // This will be the end node that actually gets called to be drawn.
            // We just pass in the vertices and vertex count to be assigned to this node.
            //AssignVerticesToNode(pVertices, numberOfVerts);
            std::vector<triangle> actualNodeTriangles;

            m_bSubDivided = false;

            actualNodeTriangles.assign(triangles,triangles+numberOfTriangles);
            AssignVerticesToNode(actualNodeTriangles);


        }

    }

void AssignVerticesToNode(std::vector<triangle> triList){
	// Since we did not subdivide this node we want to set our flag to false
	m_bSubDivided = false;

	// Allocate enough memory to hold the needed vertices for the triangles
        nodeTriangles = new triangle [triList.size()];
        m_TriangleCount=triList.size();

	for(int i=0;i<triList.size();i++)
		nodeTriangles[i]=triList[i];

	// Increase the amount of end nodes created (Nodes with vertices stored)
	/*Arreglar esto como puntero y no variable global*/

	*g_EndNodeCount++;
}

float fabs(float v) {
        return v * ((v<0) * (-1) + (v>0));
}


void drawBoundingBox(){

    point p[8];

    p[0].x=m_vCenter.x+(m_Width/2.0f);
    p[0].y=m_vCenter.y+(m_Width/2.0f);
    p[0].z=m_vCenter.z+(m_Width/2.0f);

    p[1].x=m_vCenter.x+(m_Width/2.0f);
    p[1].y=m_vCenter.y-(m_Width/2.0f);
    p[1].z=m_vCenter.z+(m_Width/2.0f);

    p[2].x=m_vCenter.x-(m_Width/2.0f);
    p[2].y=m_vCenter.y-(m_Width/2.0f);
    p[2].z=m_vCenter.z+(m_Width/2.0f);

    p[3].x=m_vCenter.x-(m_Width/2.0f);
    p[3].y=m_vCenter.y+(m_Width/2.0f);
    p[3].z=m_vCenter.z+(m_Width/2.0f);

    p[4].x=m_vCenter.x+(m_Width/2.0f);
    p[4].y=m_vCenter.y+(m_Width/2.0f);
    p[4].z=m_vCenter.z-(m_Width/2.0f);

    p[5].x=m_vCenter.x+(m_Width/2.0f);
    p[5].y=m_vCenter.y-(m_Width/2.0f);
    p[5].z=m_vCenter.z-(m_Width/2.0f);

    p[6].x=m_vCenter.x-(m_Width/2.0f);
    p[6].y=m_vCenter.y-(m_Width/2.0f);
    p[6].z=m_vCenter.z-(m_Width/2.0f);

    p[7].x=m_vCenter.x-(m_Width/2.0f);
    p[7].y=m_vCenter.y+(m_Width/2.0f);
    p[7].z=m_vCenter.z-(m_Width/2.0f);

    //for(int i=0;i<8;i++)
    //DrawPoint(p[i],Blue);


  //  glColorc(Green);

    glColor3i(171,255,0);

    glBegin(GL_LINE_LOOP);

    glVertex3f(p[0].x,p[0].y,p[0].z);
    glVertex3f(p[1].x,p[1].y,p[1].z);
    glVertex3f(p[2].x,p[2].y,p[2].z);
    glVertex3f(p[3].x,p[3].y,p[3].z);
    glVertex3f(p[0].x,p[0].y,p[0].z);
    glVertex3f(p[4].x,p[4].y,p[4].z);
    glVertex3f(p[5].x,p[5].y,p[5].z);
    glVertex3f(p[6].x,p[6].y,p[6].z);
    glVertex3f(p[7].x,p[7].y,p[7].z);
    glVertex3f(p[4].x,p[4].y,p[4].z);
    glVertex3f(p[5].x,p[5].y,p[5].z);
    glVertex3f(p[1].x,p[1].y,p[1].z);
    glVertex3f(p[2].x,p[2].y,p[2].z);
    glVertex3f(p[6].x,p[6].y,p[6].z);
    glVertex3f(p[7].x,p[7].y,p[7].z);
    glVertex3f(p[3].x,p[3].y,p[3].z);

    glEnd();
}

void drawBoundingTriangles(){
        for( int i=0; i < m_TriangleCount; i++ ){
                glColor3f(1,1,0.4);
                glBegin(GL_LINE_LOOP);
                glVertex3f( nodeTriangles[i].p0.x,nodeTriangles[i].p0.y,nodeTriangles[i].p0.z );
                glVertex3f( nodeTriangles[i].p1.x,nodeTriangles[i].p1.y,nodeTriangles[i].p1.z );
                glVertex3f( nodeTriangles[i].p2.x,nodeTriangles[i].p2.y,nodeTriangles[i].p2.z );
                glEnd();
         }
}

void DrawRecursivo(){

        drawBoundingBox();
        for(int i=0;i<8;i++)
                if(m_pOctreeNodes[i]!=NULL)
                        m_pOctreeNodes[i]->DrawRecursivo();
                        
}


bool intersect(const Ray &r) const{
    float tmin, tmax, tymin, tymax, tzmin, tzmax;

    //Caso en que el origen del rayo este dentro del cubo 
    if( r.origin.x > vertexs[1].x  && r.origin.x < vertexs[0].x  )
        if( r.origin.y > vertexs[1].y  && r.origin.y < vertexs[0].y  )
                if( r.origin.z > vertexs[1].z  && r.origin.z < vertexs[0].z  )
                        return true;
    //C�lculo de distancias de interseccion con el cubo

    tmin = (vertexs[r.sign[0]].x - r.origin.x) * r.inv_direction.x;
    tmax = (vertexs[1-r.sign[0]].x - r.origin.x) * r.inv_direction.x;
    tymin = (vertexs[r.sign[1]].y - r.origin.y) * r.inv_direction.y;
    tymax = (vertexs[1-r.sign[1]].y - r.origin.y) * r.inv_direction.y;

    if ((tmin > tymax) || (tymin > tmax))
        return false;
    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;

    tzmin = (vertexs[r.sign[2]].z - r.origin.z) * r.inv_direction.z;
    tzmax = (vertexs[1-r.sign[2]].z - r.origin.z) * r.inv_direction.z;

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;
    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;

    if ((tmax <= 0)  && (tmin <= 0))
        return false;


    return true;
  }

triangle *ProcesoRecursivo(vector origen, vector *rays, int &triNum){

        AnsiString AS;
        triangle *result;
        if(verificarTriangulos())
                AS="Todo bien";
        else
                AS="Asignacion errada";

        //ShowMessage("Numero de triangulos en el nodo: "+AnsiString(m_TriangleCount)+"\n"+AS);
        triangle *auxresult[8];
        int auxTrinum[8];
        for(int i=0;i<8;i++){
                auxresult[i]=NULL;
                auxTrinum[i]=0;
                if(m_pOctreeNodes[i] != NULL){
                        //Ray rayo (origen,rays[0]);
                        //if(m_pOctreeNodes[i]->intersect(rayo))
                                auxresult[i]=m_pOctreeNodes[i]->ProcesoRecursivo(origen, rays, auxTrinum[i]);
                }
        }
        //Agrego los triangulos de los hijos a repositorio de triangulos result
        for(int i=0;i<8;i++){
                if (auxTrinum[i]>0){
                        triangle *resultemp=new triangle[triNum+auxTrinum[i]];
                        for (int b=0; b<triNum; b++)
                                resultemp[b]=result[b];
                        for (int b=triNum; b<triNum+auxTrinum[i]; b++)
                                resultemp[b]=auxresult[i][b-triNum];
                        result=resultemp;
                        triNum=triNum+auxTrinum[i];
                }
        }
        //Agrego los triangulos del padre a repositorio de triangulos result
        if (triNum==0){
                triNum=m_TriangleCount;
                result=nodeTriangles;
        }
        else{
                triangle *resultemp=new triangle[triNum+m_TriangleCount];
                for (int b=0; b<triNum; b++)
                        resultemp[b]=result[b];
                for (int b=triNum; b<triNum+m_TriangleCount; b++)
                        resultemp[b]=nodeTriangles[b-triNum];
                result=resultemp;
                triNum=triNum+m_TriangleCount;
        }
        return result;
};

bool verificarTriangulos(){

    for(int j =0 ;j<8;j++){
        if( m_pOctreeNodes[j]!=NULL ){
                for(int i=0;i<m_TriangleCount;i++){
                        bool punto0=false,punto1=false,punto2=false;

                        if( nodeTriangles[i].p0.x > m_pOctreeNodes[j]->vertexs[1].x  && nodeTriangles[i].p0.x < m_pOctreeNodes[j]->vertexs[0].x )
                                if( nodeTriangles[i].p0.y > m_pOctreeNodes[j]->vertexs[1].y  && nodeTriangles[i].p0.y < m_pOctreeNodes[j]->vertexs[0].y )
                                        if( nodeTriangles[i].p0.z > m_pOctreeNodes[j]->vertexs[1].z  && nodeTriangles[i].p0.z < m_pOctreeNodes[j]->vertexs[0].z )
                                                punto0 = true;
                        if( nodeTriangles[i].p1.x > m_pOctreeNodes[j]->vertexs[1].x  && nodeTriangles[i].p1.x < m_pOctreeNodes[j]->vertexs[0].x )
                                if( nodeTriangles[i].p1.y > m_pOctreeNodes[j]->vertexs[1].y  && nodeTriangles[i].p1.y < m_pOctreeNodes[j]->vertexs[0].y )
                                        if( nodeTriangles[i].p1.z > m_pOctreeNodes[j]->vertexs[1].z  && nodeTriangles[i].p1.z < m_pOctreeNodes[j]->vertexs[0].z )
                                                punto1 = true;

                        if( nodeTriangles[i].p2.x > m_pOctreeNodes[j]->vertexs[1].x  && nodeTriangles[i].p2.x < m_pOctreeNodes[j]->vertexs[0].x )
                                if( nodeTriangles[i].p2.y > m_pOctreeNodes[j]->vertexs[1].y  && nodeTriangles[i].p2.y < m_pOctreeNodes[j]->vertexs[0].y )
                                        if( nodeTriangles[i].p2.z > m_pOctreeNodes[j]->vertexs[1].z  && nodeTriangles[i].p2.z < m_pOctreeNodes[j]->vertexs[0].z )
                                                punto2 = true;
                        if(punto0 && punto1 && punto2)
                                return false;
                }
        }
    }
    return true;
};


float rayTriangleIntersect(vector &orig, vector &direction, vector &v0, vector &v1, vector &v2, float &t){

            // compute plane's normal
            vector v0v1 = v1 - v0;
            vector v0v2 = v2 - v0;

            // no need to normalize
            vector N = v0v1/(v0v2); // N

            //float area2 = N.modulo();

            // Step 1: finding P

            // check if ray and plane are parallel ?
            float NdotRayDirection = N*(direction);
            if (fabs(NdotRayDirection) < KEPSILON) // almost 0
                return -1; // they are parallel so they don't intersect !

            // compute d parameter using equation 2
            float d = N*(v0);

            // compute t (equation 3)
            t = (N*(orig) + d) / NdotRayDirection;
            // check if the triangle is in behind the ray
            if (t < 0) return -1; // the triangle is behind

            std::ofstream outfile("C:\\Users\\Gadiel\\Desktop\\Intersections.txt", std::ofstream::out);

            // compute the intersection point using equation 1
            vector P = orig + direction * t;

            outfile <<"( "<<P.x<<"; "<<P.y<<"; "<<P.z<<" )"<< "\n\n";

            outfile.flush();
            outfile.close();
            //orig=P;
            // Step 2: inside-outside test
            vector C; // vector perpendicular to triangle's plane

            // edge 0
            vector edge0 = v1 - v0;

            vector vp0 = P - v0;

            C = edge0/(vp0);
            if (N*(C) < 0) return -1; // P is on the right side

            // edge 1
            vector edge1 = v2 - v1;
            vector vp1 = P - v1;
            C = edge1/(vp1);
            if (N*(C) < 0)  return -1; // P is on the right side

            // edge 2
            vector edge2 = v0 - v2;
            vector vp2 = P - v2;
            C = edge2/(vp2);
            if (N*(C) < 0) return -1; // P is on the right side;

            return t; // this ray hits the triangle
        };
};


//---------------------------------------------------------------------------

class room {
public:
    int			NP; //Number of Planes
    plane		*p; //Planes
    plane_ant		*pa;//JFLN: Planes without layers
    int			NS; //Number of Sources
    source		*s; //Sources
    source_ant		*sa;//JFLN: Sources without layers
    int			NR; //Number of Receivers
    receiver		*r; //Receivers
    receiver_ant	*ra;//JFLN: Receivers without layers
    int			NA; //Number of Audiencies
    audience		*a; //Audiencies
    int			NF; //Number of reFlectors
    reflector		*f; //reFlector
    point               *po;                     //plane Points
    float               maxd;

    void Clear() {
        if(NP>0) {
            delete[] p;
            delete[] pa;//JFLN: Old Version Planes //Bug with DXF import and using new stuff
            p=NULL;
            pa=NULL;
        }
        NP=0;
        if(NS>0) {
            delete[] s;
            delete[] sa;//JFLN: Old Version Sources
            s=NULL;
            sa=NULL;
        }
        NS=0;
        if(NR>0) {
            delete[] r;
            delete[] ra;//JFLN: Old Version Receiver
            r=NULL;
            ra=NULL;
        }
        NR=0;
        if(NA>0) {
            delete[] a;
            a=NULL;
        }
        NA=0;
        if(NF>0) {
            delete[] f;
            f=NULL;
        }
        NF=0;
    };

    void Init() {
        NP=0;
        p=NULL;
        pa=NULL;//JFLN: Old Version Planes
        NS=0;
        s=NULL;
        sa=NULL;//JFLN: Old Version Sources
        NR=0;
        r=NULL;
        ra=NULL;//JFLN: Old Version Receiver
        NA=0;
        a=NULL;
        NF=0;
        f=NULL;
    };

    inline bool Inner(point p,triangle t) {
    double a1,a2,x,y,z,x0,y0,z0,x1,y1,z1,x2,y2,z2;

    x=p.x;
    y=p.y;
    z=p.z;

    x0=t.p0.x;
    y0=t.p0.y;
    z0=t.p0.z;
    x1=t.p1.x;
    y1=t.p1.y;
    z1=t.p1.z;
    x2=t.p2.x;
    y2=t.p2.y;
    z2=t.p2.z;

    if(t.Projection==yz) {                              //Proje��o yz
        a1=-t.a0*(-y0*z+y2*z+y*z0-y2*z0-y*z2+y0*z2);
        a2=-t.a0*(y0*z-y1*z-y*z0+y1*z0+y*z1-y0*z1);
    }
    if(t.Projection==xz) {                              //Proje��o xz
        a1=-t.a0*(-x0*z+x2*z+x*z0-x2*z0-x*z2+x0*z2);
        a2=-t.a0*(x0*z-x1*z-x*z0+x1*z0+x*z1-x0*z1);
    }
    if(t.Projection==xy) {                              //Proje��o xy
        a1=-t.a0*(-x2*y0+x*y0+x0*y2-x*y2-x0*y+x2*y);
        a2=t.a0*(-x1*y0+x*y0+x0*y1-x*y1-x0*y+x1*y);
    }

    if((a1+a2<=1)&&(a1>=0)&&(a2>=0))
        return true;
    else
        return false;

    };

    inline double IntersectionDistance(vector n,point p,vector u,point o) {
    /*JFLN:
            vector n is the normal vector of the plane
            point p is one of the vertex of the plane
            vector u is the ray
            point o is the initial position of the ray
    */
    double d,m;
    m=n*u;
    //JFLN: Has to have an error tolerance
    if(m==0)
        return -1;
    d=(n*(p-o))/m;
    return d;
    };

    void MaxDistance() {
        maxd=0;
        float tmpd=0;
        for (int i1=0; i1<NP; i1++){
            for (int j1=0; j1<p[i1].NP; j1++){
                for (int i2=0; i2<NP; i2++){
                    for (int j2=0; j2<p[i2].NP; j2++){
                        if (i2==28 && j2==2)
                                i2=28;
                        tmpd=p[i1].p[j1].distancia(p[i2].p[j2]);
                        if (maxd<tmpd)
                            maxd=tmpd;
                    }
                }
            }
        }
    };

    void NewPlanes(int N) {
        int P;
        plane *tp;
        plane_ant *tpa; //JFLN: Load Old Plane data
        tp=new plane[NP+N];
        tpa=new plane_ant[NP+N]; //JFLN: Load Old Plane data
        for(P=0; P<NP; P++) {
            tp[P]=p[P];
            tpa[P]=pa[P]; //JFLN: Load Old Plane data
        }
        for(P=NP; P<NP+N; P++) {
            tp[P].Clear();
            tpa[P].Clear(); //JFLN: Load Old Plane data
        }
        if(NP>0) {
            delete[] p;
            delete[] pa; //JFLN: Load Old Plane data
            p=NULL;
            pa=NULL;
        }
        p=tp;
        pa=tpa; //JFLN: Load Old Plane data
        NP+=N;
    };

    void NewSource(int N) {
        int S;
        source *ts;
        source_ant *tsa; //JFLN: Load Old Source data
        ts=new source[NS+N];
        tsa=new source_ant[NS+N]; //JFLN: Load Old Source data
        for(S=0; S<NS; S++) {
            ts[S]=s[S];
            tsa[S]=sa[S]; //JFLN: Load Old Source data
        }
        for(S=NS; S<NS+N; S++) {
            ts[S].Clear();
            tsa[S].Clear(); //JFLN: Load Old Source data
        }
        if(NS>0) {
            delete[] s;
            delete[] sa; //JFLN: Load Old Source data
            s=NULL;
            sa=NULL;
        }
        s=ts;
        sa=tsa; //JFLN: Load Old Source data
        NS+=N;
    };

    void NewReceiver(int N) {
        int R;
        receiver *tr;
        receiver_ant *tra; //JFLN: Load Old Receiver data
        tr=new receiver[NR+N];
        tra=new receiver_ant[NR+N]; //JFLN: Load Old Receiver data
        for(R=0; R<NR; R++) {
            tr[R]=r[R];
            tra[R]=ra[R]; //JFLN: Load Old Receiver data
        }
        for(R=NR; R<NR+N; R++) {
            tr[R].Clear();
            tra[R].Clear(); //JFLN: Load Old Receiver data
        }
        if(NR>0) {
            delete[] r;
            delete[] ra; //JFLN: Load Old Receiver data
            r=NULL;
            ra=NULL;
        }
        r=tr;
        ra=tra; //JFLN: Load Old Receiver data
        NR+=N;
    };

    void NewAudience(int N) {
        int A;
        audience *ta;
        ta=new audience[NA+N];
        for(A=0; A<NA; A++)
            ta[A]=a[A];
        for(A=NA; A<NA+N; A++)
            ta[A].Clear();
        if(NA>0) {
            delete[] a;
            a=NULL;
        }
        a=ta;
        NA+=N;
    };

    void NewReflector(int N) {
        int F;
        reflector *tf;
        tf=new reflector[NF+N];
        for(F=0; F<NF; F++)
            tf[F]=f[F];
        for(F=NF; F<NF+N; F++)
            tf[F].Clear();
        if(NF>0) {
            delete[] f;
            f=NULL;
        }
        f=tf;
        NF+=N;
    };

    int * CountActiveSources() {
        int *sourcesOn;
        int NSourcesOn=0, cont=1, S;
        for(S=0; S<NS; S++)
            if(s[S].On) {
                NSourcesOn++;
            }
        if (NSourcesOn==0)
            sourcesOn=NULL;
        else{
            sourcesOn=new int[NSourcesOn+1];
            sourcesOn[0]=NSourcesOn;
            for(S=0;S<NS; S++){
                if(s[S].On) {
                    sourcesOn[cont]=S;
                    cont++;
                }
            }
        }
        return sourcesOn;
    };

    void DeletePlanes(int NSelectedPlanes,int SelectedPlane[MaxNSelectedPlanes]) {
        bool Del;
        int P,i,j=0;
        if(NP>0&&NSelectedPlanes>0) {
            plane *tp;
            tp=new plane[NP-NSelectedPlanes];
            for(P=0; P<NP; P++) {
                Del=false;
                for(i=0; i<NSelectedPlanes; i++)
                    if(P==SelectedPlane[i])
                        Del=true;
                if(!Del) {
                    tp[j]=p[P];
                    j++;
                }
            }
            delete[] p;
            p=tp;
            NP-=NSelectedPlanes;
        }
    };

    void DeleteSources(int NSelectedSources,int SelectedSource[MaxNSelectedSources]) {
        bool Del;  //Boolean for delete verification
        int S,i,j=0; //Counters
        if(NS>0&&NSelectedSources>0) {
            source *ts; //Temporal Plane Array
            ts=new source[NS-NSelectedSources]; //NS-NSS Elements in Temporal Source Array
            for(S=0; S<NS; S++) { //Check every source for delete verification
                Del=false;
                for(i=0; i<NSelectedSources; i++)
                    if(S==SelectedSource[i])
                        Del=true; //Source was marked to be deleted
                if(!Del) {
                    ts[j]=s[S]; //Sources not marked are copied in TPA
                    j++;
                }
            }
            delete[] s; //Delete Actual Source Array
            s=ts; //Actual Source Array points to Temporal Source Array
            NS-=NSelectedSources;  //Updating number of source
        }
    };

    /*void DeleteSource(int S){
        if(NS>0&&S>None){
            int i,j=0;
            source *ts;
            ts=new source[NS-1];
            for(i=0;i<NS;i++)
                if(i!=S){
                    ts[j]=s[i];
                    j++;
                }
            delete[] s;
            s=ts;
            NS--;
        }
    };*/

    void DeleteReceivers(int NSelectedReceivers,int SelectedReceiver[MaxNSelectedReceivers]) {
        bool Del;  //Boolean for delete verification
        int R,i,j=0; //Counters
        if(NR>0&&NSelectedReceivers>0) {
            receiver *tr; //Temporal Receiver Array
            tr=new receiver[NR-NSelectedReceivers]; //NS-NSS Elements in Temporal Receiver Array
            for(R=0; R<NR; R++) { //Check every receiver for delete verification
                Del=false;
                for(i=0; i<NSelectedReceivers; i++)
                    if(R==SelectedReceiver[i])
                        Del=true; //Receiver was marked to be deleted
                if(!Del) {
                    tr[j]=r[R]; //Receivers not marked are copied in TPA
                    j++;
                }
            }
            delete[] r; //Delete Actual Receiver Array
            r=tr; //Actual Receiver Array points to Temporal Receiver Array
            NR-=NSelectedReceivers;  //Updating number of receivers
        }
    };

    /*void DeleteReceiver(int R){
        if(NR>0&&R>None){
            int i,j=0;
            receiver *tr;
            tr=new receiver[NR-1];
            for(i=0;i<NR;i++)
                if(i!=R){
                    tr[j]=r[i];
                    j++;
                }
            delete[] r;
            r=tr;
            NR--;
        }
    };*/

    void DeleteAudience(int A) {
        if(NA>0&&A>None) {
            int i,j=0;
            audience *ta;
            ta=new audience[NA-1];
            for(i=0; i<NA; i++)
                if(i!=A) {
                    ta[j]=a[i];
                    j++;
                }
            delete[] a;
            a=ta;
            NA--;
        }
    };

    void DeleteReflector(int R) {
        if(NF>0&&R>None) {
            int i,j=0;
            reflector *tf;
            tf=new reflector[NF-1];
            for(i=0; i<NF; i++)
                if(i!=R) {
                    tf[j]=f[i];
                    j++;
                }
            delete[] f;
            f=tf;
            NF--;
        }
    };

    double Module(vector v) { //JFLN: Returns the vector's module
    double m;
    m=sqrt(v*v);
    return m;
    };

    vector Normal(vector v1) { //JFLN: Returns the vector's unitary vector
                                        //compare with the function unitario because this funtion is the same in MathFuntions
    double m;
    vector v2;
    m=Module(v1);
    if(m==0)
        v2=0;
    else
        v2=v1/m;
    return v2;

    };

reflection * simulation(receiver r, point origen, vector *Rays, vector v) {
    int
        LostRays=0,
        IntersectedPlane,
        LastIntersectedPlane,
        NReflections,
        TNReflections;//JFLN: Total Number of reflections
    double d1,d2;
    point p1,p2,p3; //JFLN: p3 is a point outside the room to ilustrate lost rays
    point p0;
    bool Stop;
    ray y;

    //reflection *ry; //reflexiones de los rayos
    int NRAYS=2;//numero de rayos que parten de la fuente
    reflection *ry;
    ry=new reflection[2]; //JFLN: Allocate memory for new reflections
    //tantas reflexiones como numero de rayos
    NReflections=0;
    TNReflections=0;//JFLN: Total Number of reflections
    point posicionFuente=origen;
    //Ray-tracing
    //simulacion rayo por rayo
    for(int RAY=0; RAY<NRAYS; RAY++) {
        y.v=Rays[RAY];  //JFLN: Direction of Ray
        y.p=posicionFuente;//r.s[0].p;   //JFLN: Position of Ray
        IntersectedPlane=-1;
        LastIntersectedPlane=-1; //no se utiliza
        Stop=false;
        ry[RAY].N = 0; //Julio
        ry[RAY].r[0] = y.p;//Julio
        ry[RAY].lost = false;//JFLN: Lost reflection
        ry[RAY].Ray = RAY;//JFLN: What Ray Belongs to
        while(!Stop) { //inicio simulacion
            MaxDistance(); //MAXDOUBLE;//JFLN: Must create function for calculating the larger distance between two points of the room
            d1=maxd;

            std::ofstream outfile("C:\\Users\\Gadiel\\Desktop\\Directions.txt", std::ofstream::out);
            for(int P=0; P<NP; P++) { //JFLN: Goes through all the planes
                if(((p[P].n*y.v)<0) && (P!=LastIntersectedPlane)) { //JFLN: If escalar product between plane's normal and direction of ray is minor than 0 and current plane is diferent of last intersected plane
                    d2=IntersectionDistance(p[P].n,p[P].p[0],y.v,y.p); //JFLN: Calculate distance between ray and plane

                    outfile <<"("<<y.v.x<<"; "<<y.v.y<<"; "<<y.v.z<<")"<<" \n";
                    outfile <<"("<<y.p.x<<"; "<<y.p.y<<"; "<<y.p.z<<")"<<" \n \n";
                    if((d2>0.000001) && (d2<d1)/*para ver precedencia con cual plano choca primero*/) { //JFLN: If distance between plane and initial position of ray is bigger than 0 and d2 minor than d1
                        //revisa si el vector interseca con el plano
                        p2=y.p+(y.v*d2);//JFLN: Point 2 equal to position of ray plus the distance
                        //revisa si el rayo interseca con los triangulos interiores al plano pequeño
                        for(int T=0; T<p[P].NT; T++)
                            if(Inner(p2,p[P].t[T])) {
                                d1=d2;
                                p1=p2;
                                outfile <<d1<<" \n \n";
                                IntersectedPlane=P;
                                T=p[P].NT;//terminar for
                                //guardar punto en un arreglo
                            }
                    }
                }
            }
             outfile.close();

            //p3=y.p+(y.v*d3);//JFLN: p3 is a point outside the room to ilustrate lost rays

            if(d1<MAXDOUBLE) { //si se interseco

                y.d+=Module(p1-y.p);//calcular distancia viajada del rayo
                y.p=p1;//inserta punto inicio del rayo
                //Calcular vector reflexion
                //OJO OJO OJO OJO OJO Revisar formula
                y.v=Normal(y.v-(p[IntersectedPlane].n*(y.v*p[IntersectedPlane].n*2)));
                LastIntersectedPlane=IntersectedPlane;
                NReflections++;
                TNReflections += NReflections; //JFLN: Total Number of reflections
                ry[RAY].r[NReflections] = p1;//JFLN: Only if is inner point of triangle
                ry[RAY].N++;//JFLN: Only if is inner point of triangle

                //maximo 50 reflexiones
                if(NReflections>50) { //if(TNReflections>50)
                    Stop=true;
                    NReflections=0; //JFLN: I think NReflections has to be 0 for the next ray
                }
            } else {
                NReflections++;
                ry[RAY].lost = true;//JFLN: Lost reflection
                ry[RAY].r[NReflections] = p3;//JFLN: Point outside room
                ry[RAY].N++;//JFLN: Point outside room
                LostRays++;
                Stop=true;
                NReflections=0; //JFLN: I think NReflections has to be 0 for the next ray
            }
        }
    }
    return ry;
    };

reflection *simulationMoller(Ray r, triangle *t, int numTriangles){
        int index=-1,LastIntersectedPlane,IntersectedPlane,NReflections,TNReflections;
        float distanceTriangle=FLT_MAX; //cambiar a double y valor maxdouble
        float currentDistance=0;
        reflection *rflx=new reflection();

        vector v0;
        vector v1;
        vector v2;

        /*r.origin.x=10;
        r.origin.y=10;
        r.origin.z=10;

        r.direction.x=0.25;
        r.direction.y=0.62;
        r.direction.z=0.74;*/

        /*v0.x=0;
        v0.y=0;
        v0.z=0;

        v1.x=0;
        v1.y=0;
        v1.z=0;

        v2.x=0;
        v2.y=0;
        v2.z=0;*/

        for (int i =0;i<50;i++)//calcular 50 reflexiones
        {
                for(int j=0;j<numTriangles;j++)
                        if(t[j].rayTriangleIntersect(r.origin, r.direction, v0, v1, v2, currentDistance))
                        {
                              if(currentDistance<distanceTriangle){ //Buscar el triangulo mas cercano
                                        distanceTriangle=currentDistance;
                                        index=j;
                                }
                        }
                        //Calcular Reflexion
                        if(index!=-1)
                        {
                                //Actualizar direccion del rayo con el triangulo j
                                r.direction=r.Normal(r.direction-(p[IntersectedPlane].n*(r.direction*p[IntersectedPlane].n*2)));
                                //Actualizar origen del rayo con el triangulo j
                                r.origin=r.origin+(currentDistance);
                                rflx[0].r[i].x=r.origin.x;
                                rflx[0].r[i].y=r.origin.y;
                                rflx[0].r[i].z=r.origin.z;
                        }
        }
        return rflx;
        };
};

/*reflection *simulationArbol(Octree octree,Ray ray){

        std::vector<nodes> triList
        // Allocate enough memory to hold the needed vertices for the triangles
        nodes = new nodes [triList.size()];
       	for(int i=0;i<triList.size();i++)
		nodes[i]=triList[i];

};*/

//---------------------------------------------------------------------------
class nuevomatdatabase {
public:
    int             NM; //Number of Materials
    nuevomaterial   *m; //Materials

    void NewMaterial(int N) {
        int M;
        nuevomaterial *tm;
        tm=new nuevomaterial[NM+N];
        for(M=0; M<NM; M++)
            tm[M]=m[M];
        for(M=NM; M<NM+N; M++)
            tm[M].Clear();
        if(NM>0)
            delete[] m;
        m=tm;
        NM+=N;
    };

    void DeleteMaterial(int M) {
        if(NM>0&&M>-1) {
            int i,j=0;
            nuevomaterial *tm;
            tm=new nuevomaterial[NM-1];
            for(i=0; i<NM; i++)
                if(i!=M) {
                    tm[j]=m[i];
                    j++;
                }
            delete[] m;
            m=tm;
            NM--;
        }
    };

    void Clear() {
        if(NM>0)
            delete[] m;
        m=NULL;
        NM=0;
    };

    void Init() {
        NM=0;
        m=NULL;
    };
};
//---------------------------------------------------------------------------
class database {
public:
    int         NM; //Number of Materials
    material    *m; //Materials
    int         ND; //Number of source Diretivities
    directivity *d; //source Diretivities

    void NewMaterial(int N) {
        int M;
        material *tm;
        tm=new material[NM+N];
        for(M=0; M<NM; M++)
            tm[M]=m[M];
        for(M=NM; M<NM+N; M++)
            tm[M].Clear();
        if(NM>0)
            delete[] m;
        m=tm;
        NM+=N;
    };

    void NewDirectivity(int N) {
        int D;
        directivity *td;
        td=new directivity[ND+N];
        for(D=0; D<ND; D++)
            td[D]=d[D];
        for(D=ND; D<ND+N; D++)
            td[D].Clear();
        if(ND>0)
            delete[] d;
        d=td;
        ND+=N;
    };

    void DeleteMaterial(int M) {
        if(NM>0&&M>-1) {
            int i,j=0;
            material *tm;
            tm=new material[NM-1];
            for(i=0; i<NM; i++)
                if(i!=M) {
                    tm[j]=m[i];
                    j++;
                }
            delete[] m;
            m=tm;
            NM--;
        }
    };

    void DeleteDirectivity(int D) {
        if(ND>0&&D>-1) {
            int i,j=0;
            directivity *td;
            td=new directivity[ND-1];
            for(i=0; i<ND; i++)
                if(i!=D) {
                    td[j]=d[i];
                    j++;
                }
            delete[] d;
            d=td;
            ND--;
        }
    };

    void Clear() {
        if(NM>0)
            delete[] m;
        m=NULL;
        NM=0;
        if(ND>0)
            delete[] d;
        d=NULL;
        ND=0;
    };

    void Init() {
        NM=0;
        m=NULL;
        ND=0;
        d=NULL;
    };
};
//---------------------------------------------------------------------------
class results {
public:
    int             NRR;    //Number of Receiver Results
    rresults        *rr;    //Receiver Results
    rresults_new    *rrn;   //New Receiver Results
    int             NAR;    //Number of Audience Results
//allocate memory for N new rresults
    void NewRResults(int N) {
        int RR;
        rresults *trr;
        rresults_new *trrn;
        trr=new rresults[NRR+N];
        trrn=new rresults_new[NRR+N];
        for(RR=0; RR<NRR; RR++) {
            trr[RR]=rr[RR];
            trrn[RR]=rrn[RR];
        }
        for(RR=NRR; RR<NRR+N; RR++) {
            trr[RR].Init();
            trrn[RR].Init();
        }
        if(NRR>0) {
            delete[] rr;
            rr=NULL;
            delete[] rrn;
            rrn=NULL;
        }
        rr=trr;
        rrn=trrn;
        NRR+=N;
    };
//delete one rresults
    void DeleteRResults(int RR) {
        if(NRR>0&&RR>None) {
            int i,j=0;
            rresults *trr;
            rresults_new *trrn;
            trr=new rresults[NRR-1];
            trrn=new rresults_new[NRR-1];
            for(i=0; i<NRR; i++)
                if(i!=RR) {
                    trr[j]=rr[i];
                    trrn[j]=rrn[i];
                    j++;
                }
            rr[RR].Clear();
            rrn[RR].Clear();
            delete[] rr;
            delete[] rrn;
            rr=trr;
            rrn=trrn;
            NRR--;
        }
    };
//clear
    void Clear() {
        for(int RR=0; RR<NRR; RR++) {
            rr[RR].Clear();
            rrn[RR].Clear();
        }
        if(NRR>0) {
            delete[] rr;
            delete[] rrn;
            rr=NULL;
            rrn=NULL;
        }
        NRR=0;
        NAR=0;
    };
//initialize
    void Init() {
        NRR=0;
        rr=NULL;
        rrn=NULL;
        NAR=0;
    };
};
//---------------------------------------------------------------------------
class impulseresponse {
public:
    int         NumSou,                     //JFLN: number of sources
    NumRec,                     //JFLN: number of receivers
    StpTim[NB+1];                 //JFLN: expected stop time [number of octave bands]
    float       ***SpecularIR,              //JFLN: specular impulse response
    ***DiffuseIR,               //JFLN: diffuse impulse response
    ***HybridIR,                //JFLN: hybrid impulse response
    ***LFIR,                    //JFLN: lateral Fraction impulse response
    ***LFCIR,                   //JFLN: lateral Fraction Cosine impulse response
    ***DecayCurve;              //JFLN: decay curve
    //JFLN: Constructor
    impulseresponse() {
        NumSou = 0;
        NumRec = 0;
        for(int b=0; b<NB+1; b++) {
            StpTim[b]=0;
        }
        SpecularIR = NULL;
        DiffuseIR = NULL;
        HybridIR = NULL;
        LFIR = NULL;
        LFCIR = NULL;
        DecayCurve = NULL;
    };
    /*
    //JFLN: Destructor
    ~impulseresponse(){
        //JFLN: Do something here if necessary
    };
    */
    //JFLN: create and clear discrete impulsive response matrixes
    bool CreateImpResMat(int NS, int NR, int* StopTime, int MaxStopTime) { //JFLN: (Sources, Receivers)
        try {
            NumSou = NS;
            NumRec = NR;
            for(int b=0; b<NB; b++) {
                StpTim[b]=StopTime[b];
            }
            StpTim[NB]=MaxStopTime;//JFLN: longest stop time
            SpecularIR=new float**[NumRec];
            DiffuseIR=new float**[NumRec];
            HybridIR=new float**[NumRec];
            LFIR=new float**[NumRec];
            LFCIR=new float**[NumRec];
            DecayCurve=new float**[NumRec];
            for(int r=0; r<NumRec; r++) {
                //JFLN: Allocate memory for each band and for the global result
                SpecularIR[r]=new float*[NB+1];
                DiffuseIR[r]=new float*[NB+1];
                HybridIR[r]=new float*[NB+1];
                LFIR[r]=new float*[NB+1];
                LFCIR[r]=new float*[NB+1];
                DecayCurve[r]=new float*[NB+1];
                for(int b=0; b<NB+1; b++) {
                    //For each Receptor x band result allocate memory for each time unit
                    SpecularIR[r][b]=new float[StpTim[b]];
                    DiffuseIR[r][b]=new float[StpTim[b]];
                    HybridIR[r][b]=new float[StpTim[b]];
                    LFIR[r][b]=new float[StpTim[b]];
                    LFCIR[r][b]=new float[StpTim[b]];
                    DecayCurve[r][b]=new float[StpTim[b]];
                    for(int t=0; t<StpTim[b]; t++) { //JFLN: clear discrete impulsive response matrixes
                        SpecularIR[r][b][t]=0.0;
                        DiffuseIR[r][b][t]=0.0;
                        HybridIR[r][b][t]=0.0;
                        LFIR[r][b][t]=0.0;
                        LFCIR[r][b][t]=0.0;
                        DecayCurve[r][b][t]=0.0;
                    }
                }
            }
            return true;
        } catch(EAccessViolation& ba) {
            ShowMessage( ba.Message );
            return false;
        } catch(...) {
            return false;
        }
    };

    //delete discrete impulsive response matrixes
    bool DeleteImpResMat() {
        try {
            for(int r=0; r<NumRec; r++) {
                for(int b=0; b<NB+1; b++) {
                    delete[] SpecularIR[r][b];
                    delete[] DiffuseIR[r][b];
                    delete[] HybridIR[r][b];
                    delete[] LFIR[r][b];
                    delete[] LFCIR[r][b];
                    delete[] DecayCurve[r][b];
                }
                delete[] SpecularIR[r];
                delete[] DiffuseIR[r];
                delete[] HybridIR[r];
                delete[] LFIR[r];
                delete[] LFCIR[r];
                delete[] DecayCurve[r];
            }
            delete[] SpecularIR;
            delete[] DiffuseIR;
            delete[] HybridIR;
            delete[] LFIR;
            delete[] LFCIR;
            delete[] DecayCurve;
            SpecularIR=NULL;
            DiffuseIR=NULL;
            HybridIR=NULL;
            LFIR=NULL;
            LFCIR=NULL;
            DecayCurve=NULL;
            NumSou = 0;
            NumRec = 0;
            for(int b=0; b<NB+1; b++) {
                StpTim[b]=0;
            }
            return true;
        } catch(...) {
            return false;
        }
    };
};
//---------------------------------------------------------------------------
class qltyacouparam {
public:
    int         NumSou,                     //JFLN: number of sources
    NumRec;                     //JFLN: number of receivers
    float       **T30,                      //T30
    **EDT,                      //EDT
    **D50,                      //D50
    **C80,                      //C80
    **TS,                       //TS
    **G,                        //G
    **LF,                       //LF
    **LFC,                      //LFC
    **D80,                      //D80
    **C50,                      //C50
    **LG,                       //LG
    **ST1;                      //ST1
    //JFLN: Constructor
    qltyacouparam() {
        NumSou = 0;
        NumRec = 0;
        T30=NULL;
        EDT = NULL;
        D50 = NULL;
        D80 = NULL;
        C50 = NULL;
        C80 = NULL;
        TS = NULL;
        G = NULL;
        LG = NULL;
        LF = NULL;
        LFC = NULL;
        ST1 = NULL;
    };
    /*
    //JFLN: Destructor
    ~qltyacouparam(){
        //JFLN: Do something here if necessary
    };
    */
    //JFLN: create and clear quality parameters matrixes
    bool CreateQltyParamMat(int NS, int NR) { //JFLN: (Sources, Receivers)
        try {
            NumSou = NS;
            NumRec = NR;
            T30 = new float*[NumRec];
            EDT = new float*[NumRec];
            D50 = new float*[NumRec];
            D80 = new float*[NumRec];
            C50 = new float*[NumRec];
            C80 = new float*[NumRec];
            TS = new float*[NumRec];
            G = new float*[NumRec];
            LG = new float*[NumRec];
            LF = new float*[NumRec];
            LFC = new float*[NumRec];
            ST1 = new float*[NumRec];
            for(int r=0; r<NumRec; r++) { //JFLN: Allocate memory for each band and for the global result
                T30[r] = new float[NB+1];
                EDT[r] = new float[NB+1];
                D50[r] = new float[NB+1];
                D80[r] = new float[NB+1];
                C50[r] = new float[NB+1];
                C80[r] = new float[NB+1];
                TS[r] = new float[NB+1];
                G[r] = new float[NB+1];
                LG[r] = new float[NB+1];
                LF[r] = new float[NB+1];
                LFC[r] = new float[NB+1];
                ST1[r] = new float[NB+1];
                for(int b=0; b<NB+1; b++) { //JFLN: clear quality parameters matrixes
                    T30[r][b] = 0.0;
                    EDT[r][b] = 0.0;
                    D50[r][b] = 0.0;
                    D80[r][b] = 0.0;
                    C50[r][b] = 0.0;
                    C80[r][b] = 0.0;
                    TS[r][b] = 0.0;
                    G[r][b] = 0.0;
                    LG[r][b] = 0.0;
                    LF[r][b] = 0.0;
                    LFC[r][b] = 0.0;
                    ST1[r][b] = 0.0;
                }
            }
            return true;
        } catch(EAccessViolation& ba) {
            ShowMessage( ba.Message );
            return false;
        } catch(...) {
            return false;
        }
    };

    //delete quality parameters matrixes
    bool DeleteQltyParamMat() {
        try {
            for(int r=0; r<NumRec; r++) {
                delete[] T30[r];
                delete[] EDT[r];
                delete[] D50[r];
                delete[] D80[r];
                delete[] C50[r];
                delete[] C80[r];
                delete[] TS[r];
                delete[] G[r];
                delete[] LG[r];
                delete[] LF[r];
                delete[] LFC[r];
                delete[] ST1[r];
            }
            delete[] T30;
            delete[] EDT;
            delete[] D50;
            delete[] D80;
            delete[] C50;
            delete[] C80;
            delete[] TS;
            delete[] G;
            delete[] LG;
            delete[] LF;
            delete[] LFC;
            delete[] ST1;
            T30=NULL;
            EDT=NULL;
            D50=NULL;
            D80=NULL;
            C50=NULL;
            C80=NULL;
            TS=NULL;
            G=NULL;
            LG=NULL;
            LF=NULL;
            LFC=NULL;
            ST1=NULL;
            NumSou=0;
            NumRec=0;
            return true;
        } catch(...) {
            return false;
        }
    };
};
//---------------------------------------------------------------------------
class transition {
public:
    int         NumEle,                     //JFLN: number of triangle elements
    NumSou,                     //JFLN: number of sources
    NumRec,                     //JFLN: number of receivers
    StpTim[NB];                 //JFLN: expected stop time [number of octave bands]
    float       ***Transition,              //JFLN: energy transition matrix
    ***TransitionReceiver,      //JFLN: energy transition between triangle element and receptor
    ****ElementsEnergy;          //JFLN: elements energy matrix
    //****ElementsEnergyG;       //JFLN: elements energy matrix
    int         **TransitionTime,           //JFLN: transition time between elements [ms]
    **TransitionTimeReceiver;   //JFLN: transition time between diffuse element and receptor [ms]
    vector      **TransitionVector;         //JFLN: transition incidence direction
    //JFLN: Constructor
    transition() {
        NumEle=0;
        NumSou=0;
        NumRec=0;
        for(int b; b<NB; b++) {
            StpTim[b]=0;
        }
        Transition=NULL;
        TransitionReceiver=NULL;
        ElementsEnergy=NULL;
        //ElementsEnergyG=NULL;
        TransitionTime=NULL;
        TransitionTimeReceiver=NULL;
        TransitionVector=NULL;

    };
    /*
    //JFLN: Destructor
    ~transition(){
        //JFLN: Do something here if necessary
    };
    */
    //JFLN: create and clear energy transition matrixes, elements energy matrix and time transition matrixes
    bool CreateEneTransMat(int NE, int NS, int NR, int* StopTime) { //JFLN: (Elements, Sources, Receivers, StopTime[Band])
        try {
            NumEle=NE;
            NumSou=NS;
            NumRec=NR;
            for(int b=0; b<NB; b++) {
                StpTim[b]=StopTime[b];
            }
            Transition  = new float**[NumEle];
            TransitionReceiver  = new float**[NumEle];
            ElementsEnergy = new float***[NumEle];
            //ElementsEnergyG = new float***[NumEle];
            TransitionTime = new int*[NumEle];
            TransitionTimeReceiver = new int*[NumEle];
            TransitionVector = new vector*[NumEle];
            for(int ea=0; ea<NumEle; ea++) {
                Transition[ea] = new float*[NumEle];
                TransitionReceiver[ea] = new float*[NumRec];
                ElementsEnergy[ea] = new float**[NumSou];
                //ElementsEnergyG[ea] = new float**[NumSou];
                TransitionTime[ea] = new int[NumEle];
                TransitionTimeReceiver[ea] = new int[NumRec];
                TransitionVector[ea] = new vector[NumRec];

                for(int eb=0; eb<NumEle; eb++) {
                    Transition[ea][eb] = new float[NB];
                    for(int b=0; b<NB; b++) {
                        Transition[ea][eb][b]=0.0;//clear Transition matrix
                    }
                    TransitionTime[ea][eb]=0;//clear TransitionTime matrix

                }
                for(int r=0; r<NumRec; r++) {
                    TransitionReceiver[ea][r] = new float[NB];
                    for(int b=0; b<NB; b++) {
                        TransitionReceiver[ea][r][b]=0.0;//clear TransitionReceiver matrix
                    }
                    TransitionTimeReceiver[ea][r]=0;//clear TransitionTimeReceiver matrix
                    TransitionVector[ea][r].x=0.0;//clear TransitionVector matrix
                    TransitionVector[ea][r].y=0.0;//clear TransitionVector matrix
                    TransitionVector[ea][r].z=0.0;//clear TransitionVector matrix
                }
                for(int s=0; s<NumSou; s++) {
                    ElementsEnergy[ea][s] = new float*[NB];
                    //ElementsEnergyG[ea] = new float*[NB];
                    for(int b=0; b<NB; b++) {
                        ElementsEnergy[ea][s][b] = new float[StpTim[b]];
                        //ElementsEnergyG[ea][s][b] = new float[StpTim[b]];
                        for(int t=0; t<StpTim[b]; t++) {
                            ElementsEnergy[ea][s][b][t]=0.0;//clear ElementsEnergy matrix
                            //ElementsEnergyG[ea][s][b][t]=0.0;//clear Global ElementsEnergy matrix
                        }
                    }
                }
            }
            return true;
        } catch(EAccessViolation& ba) {
            ShowMessage( ba.Message );
            return false;
        } catch(...) {
            return false;
        }
    };

    //delete energy transition matrixes, elements energy matrix and time transition matrixes
    bool DeleteEneTransMat() {
        try {
            for(int ea=0; ea<NumEle; ea++) {
                for(int eb=0; eb<NumEle; eb++) {
                    delete[] Transition[ea][eb];
                }
                for(int r=0; r<NumRec; r++) {
                    delete[] TransitionReceiver[ea][r];
                }
                for(int s=0; s<NumSou; s++) {
                    for(int b=0; b<NB; b++) {
                        delete[] ElementsEnergy[ea][s][b];
                        //delete[] ElementsEnergyG[ea][s][b];
                    }
                    delete[] ElementsEnergy[ea][s];
                    //delete[] ElementsEnergyG[ea][s];
                }
                delete[] Transition[ea];
                delete[] TransitionReceiver[ea];
                delete[] ElementsEnergy[ea];
                //delete[] ElementsEnergyG[ea];
                delete[] TransitionTime[ea];
                delete[] TransitionTimeReceiver[ea];
                delete[] TransitionVector[ea];
            }
            delete[] Transition;
            delete[] TransitionReceiver;
            delete[] ElementsEnergy;
            //delete[] ElementsEnergyG;
            delete[] TransitionTime;
            delete[] TransitionTimeReceiver;
            delete[] TransitionVector;
            Transition=NULL;
            TransitionReceiver=NULL;
            ElementsEnergy=NULL;
            //ElementsEnergyG=NULL;
            TransitionTime=NULL;
            TransitionTimeReceiver=NULL;
            TransitionVector=NULL;
            NumEle=0;
            NumSou=0;
            NumRec=0;
            for(int b=0; b<NB; b++) {
                StpTim[b]=0;
            }
            return true;
        } catch(...) {
            return false;
        }
    };
};
//---------------------------------------------------------------------------

/*class Ray{

        public:
        vector origin;
        vector direction;
        vector inv_direction;
        int sign[3];

        Ray(){};
        Ray(vector o, vector d) {
                origin = o;
                direction = d;
                inv_direction.x=1/d.x;
                inv_direction.x=1/d.y;
                inv_direction.x=1/d.z;
                sign[0] = (inv_direction.x < 0);
                sign[1] = (inv_direction.y < 0);
                sign[2] = (inv_direction.z < 0);
        }

        Ray(const Ray &r) {
                origin = r.origin;
                direction = r.direction;
                inv_direction = r.inv_direction;
                sign[0] = r.sign[0]; sign[1] = r.sign[1]; sign[2] = r.sign[2];
        }
        double Module(vector v) { //JFLN: Returns the vector's module
                double m;
                m=sqrt(v*v);
        return m;
        };

        vector Normal(vector v1) { //JFLN: Returns the vector's unitary vector
                                        //compare with the function unitario because this funtion is the same in MathFuntions
                                double m;
                                vector v2;
                                m=Module(v1);
                                if(m==0)
                                v2=0;
                                else
                                v2=v1/m;
                                return v2;
        };
};*/

//---------------------------------------------------------------------------

/*class Box {
  public:
    point vertexs[2];
    Box() { }
    Box(const point &min, const point &max) {
      vertexs[0] = min;
      vertexs[1] = max;
    }

bool intersect(const Ray &r) const{
    float tmin, tmax, tymin, tymax, tzmin, tzmax;

    tmin = (vertexs[r.sign[0]].x - r.origin.x) * r.inv_direction.x;
    tmax = (vertexs[1-r.sign[0]].x - r.origin.x) * r.inv_direction.x;
    tymin = (vertexs[r.sign[1]].y - r.origin.y) * r.inv_direction.y;
    tymax = (vertexs[1-r.sign[1]].y - r.origin.y) * r.inv_direction.y;

    if ((tmin > tymax) || (tymin > tmax))
        return false;
    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;

    tzmin = (vertexs[r.sign[2]].z - r.origin.z) * r.inv_direction.z;
    tzmax = (vertexs[1-r.sign[2]].z - r.origin.z) * r.inv_direction.z;

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;
    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;

    return true;
  }
};*/

//---------------------------------------------------------------------------




#endif
