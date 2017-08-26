//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <gl\gl.h>
#include <gl\glu.h>
#include <ctype.h>
#include <vector>
#include "Classes.h"
#include "MathFunctions.h"
#include "Definitions.h"
#include <fstream>
#include <iostream>
#include "UnitView.h"
#define MAXDOUBLE 1000000
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ExtCtrls"
#pragma resource "*.dfm"

TFormView *FormView;
//---------------------------------------------------------------------------
__fastcall TFormView::TFormView(TComponent* Owner) : TForm(Owner) {
    int i,j;
    Application->OnIdle=IdleLoop;
    FormView->Top=0;//ToolBarHeight;
    FormView->Left=0;
    FormView->Height=FormView->ClientHeight;
    FormView->Width=FormView->ClientWidth;

//default colors
    Red.R      =1;
    Red.G      =0.65;
    Red.B      =0.65;;
    Green.R    =0.65;
    Green.G    =1;
    Green.B    =0.65;
    Blue.R     =0.65;
    Blue.G     =0.65;
    Blue.B     =1;
    Yellow.R   =1;
    Yellow.G   =1;
    Yellow.B   =0.4;
    LightGray.R=0.55;
    LightGray.G=0.55;
    LightGray.B=0.55;
    DarkGray.R =0.4;
    DarkGray.G =0.4;
    DarkGray.B =0.4;
//default values
    a=19*PI/60;
    b=13*PI/60;
    d=10;
    f=0.5;      //approximately 30 degrees (or PI*30/180 rad)
    g=0.2;
    e=40;

    c=0;
    w=ClientWidth;
    h=ClientHeight;
    cuartoCargado=false;
    bandSim=false;
}
//---------------------------------------------------------------------------
void __fastcall TFormView::FormCreate(TObject *Sender) {
//OpenGL initialize
    hdc=GetDC(Handle);
    SetPixelFormatDescriptor();
    hrc=wglCreateContext(hdc);
    if(hrc==NULL)
        ShowMessage("hrc==NULL");
    if(wglMakeCurrent(hdc,hrc)==false)
        ShowMessage("Could not MakeCurrent");
//OpenGL default parameters
    glClearColor(0.6,0.6,0.6,0.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0,1.0);
    glLineWidth(1);
    glPointSize(4);

    a   =19*PI/60;
    b   =13*PI/60;
    d   =10;
    f   =0.5;      //approximately 30 degrees (or PI*30/180 rad)
    g   =0.2;
    e   =40;
    c   =0;
}
//---------------------------------------------------------------------------

void __fastcall TFormView::SetPixelFormatDescriptor() {
//OpenGL initialize
    PIXELFORMATDESCRIPTOR pfd= {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        24,
        0,0,0,0,0,0,
        0,0,
        0,0,0,0,0,
        32,
        0,
        0,
        PFD_MAIN_PLANE,
        0,
        0,0,
    };
    PixelFormat=ChoosePixelFormat(hdc,&pfd);
    SetPixelFormat(hdc,PixelFormat,&pfd);
}


void __fastcall TFormView::IdleLoop(TObject*,bool& done) {
//draw scene
    DrawScene();
}

inline void __fastcall TFormView::glVertexp(point p)
{
//draw point
    glVertex3f(p.x,p.y,p.z);
}
//---------------------------------------------------------------------------
inline void __fastcall TFormView::glColorc(color c)
{
//color RGB
    glColor3f(c.R,c.G,c.B);
}
//---------------------------------------------------------------------------
void __fastcall TFormView::DrawScene(void) {
    int     i,j;
    double  df, //Distance of Front-plane of view
    db; //Distance of Back-plane of view

    /*
    //default values
        a=19*PI/60; //Alpha [horizontal viewer angle]
        b=13*PI/60; //Beta [vertical viewer angle]
        d=30;	    //observer Distance
        f=0.5;      //Fov [focus angle] //approximately 30 degrees (or PI*30/180 rad)
        g=0.2;	    //Grig space
        e=40;	    //grid Elements
        c=0;	    //Central point
        w=ClientWidth;
        h=ClientHeight;
    */

    //OpenGL parameters
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    db=sqrt(3*e*g*e*g+2*e*g*(abs(c.x)+abs(c.y)+abs(c.z))+c.x*c.x+c.y*c.y+c.z*c.z);
    if(d>db)
        df=db;
    else
        df=0.99*d;
    /*void gluPerspective(	GLdouble  	fovy,
    GLdouble  	aspect,
    GLdouble  	zNear,
    GLdouble  	zFar);*/
    gluPerspective(180*f/PI,double(w)/double(h),d-df,d+db);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    o.x=d*cos(b)*cos(a)+c.x;
    o.y=d*cos(b)*sin(a)+c.y;
    o.z=d*sin(b)+c.z;
    Up.x=-sin(a);
    Up.y=cos(a);
    Up.z=0;
    Up=Normal(Up/(c-o));
    /*
    void gluLookAt(	GLdouble eyeX,
    GLdouble eyeY,
    GLdouble eyeZ,
    GLdouble centerX,
    GLdouble centerY,
    GLdouble centerZ,
    GLdouble upX,
    GLdouble upY,
    GLdouble upZ);
    */
    gluLookAt(o.x,o.y,o.z,c.x,c.y,c.z,Up.x,Up.y,Up.z);

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    //Drawroom
    if(cuartoCargado)
        for (i=0;i<r.NP;i++)
                DrawPlane(r.p[i],i);

    //Definir rayos a graficar

    if (bandSim==true){
    for(j=0;j<2;j++){
        for(i=0;i<ry[j].N-1;i++){
            color temp;
            vector vecgra;
            float modvg,modvgs;
            if(j==0){
                temp=Yellow;
                vecgra=vec_gra[i];
                modvg=mod_vg[i];
                modvgs=mod_vg[i+1];
            }
            if(j==1){
                temp=Red;
                vecgra=vec_gra2[i];
                modvg=mod_vg2[i];
                modvgs=mod_vg2[i+1];
            }
            if(distancia>modvg && distancia<modvgs)
                DrawVector(ry[j].r[i], vecgra, true, modvg, temp);
            else if(distancia>modvgs)
                DrawVector(ry[j].r[i], vecgra, false, modvg, temp);
        }
    }
    }

    //draw grid
        DrawGrid();
    //draw coordinates
    glDisable(GL_DEPTH_TEST);
    DrawAxis();
    if(cuartoCargado)
    {

        DrawPoint( octree.m_vCenter, Red);

        octree.drawBoundingBox();
        octree.drawBoundingTriangles();
        octree.DrawRecursivo();


    }

    glEnable(GL_DEPTH_TEST);
    //swap OpenGL buffers
    SwapBuffers(hdc);
}


//---------------------------------------------------------------------------
/*void __fastcall TFormView::drawBoundingBox(point m_vCenter,float m_Width){

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

    for(int i=0;i<8;i++)
    DrawPoint(p[i],Blue);


    glColorc(Green);
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

} */

/*inline void __fastcall TFormView::octreeDrawRecursivo(){
        drawBoundingBox();
        for(int i=0;i<8;i++;){
                if(subNode[i]=!NULL)
                        octreeDrawRecursivo();
        }
}*/

inline void __fastcall TFormView::DrawPoint(point p,color c){
        glColorc(c);
    glPushMatrix();
              glTranslatef(p.x,p.y,p.z);
              gluSphere(gluNewQuadric(), .05, 35 , 56);
    glPopMatrix();
}

inline void __fastcall TFormView::DrawGrid(void) {
    double l;
//inner lines
    glColorc(LightGray);
    glBegin(GL_LINES);
    for(l=g; l<e*g-g/2; l+=g) {
        glVertex3f(l,-e*g,0);
        glVertex3f(l,e*g,0);
        glVertex3f(-e*g,l,0);
        glVertex3f(e*g,l,0);
    }
    for(l=-g; l>-e*g+g/2; l-=g) {
        glVertex3f(l,-e*g,0);
        glVertex3f(l,e*g,0);
        glVertex3f(-e*g,l,0);
        glVertex3f(e*g,l,0);
    }
    glEnd();
//contour lines
    glColorc(DarkGray);
    glBegin(GL_LINE_LOOP);
    glVertex3f(e*g,e*g,0);
    glVertex3f(e*g,-e*g,0);
    glVertex3f(-e*g,-e*g,0);
    glVertex3f(-e*g,e*g,0);
    glEnd();
//axis lines
    glBegin(GL_LINES);
    glVertex3f(-e*g,0,0);
    glVertex3f(e*g,0,0);
    glVertex3f(0,-e*g,0);
    glVertex3f(0,e*g,0);
    glVertex3f(0,0,-e*g);
    glVertex3f(0,0,e*g);
    glEnd();
}
//


inline void __fastcall TFormView::DrawCoordinate(point p,color c) {
//draw coordinates
    glColorc(c);
    glBegin(GL_LINES);
    glVertex3f(p.x,0,0);
    glVertex3f(p.x,p.y,0);
    glVertex3f(0,p.y,0);
    glVertex3f(p.x,p.y,0);
    glVertex3f(p.x,p.y,0);
    glVertex3f(p.x,p.y,p.z);
    glEnd();

}


inline void __fastcall TFormView::DrawAxis(void) {
//x, y and z coloured axis
    glLineWidth(2);
    glColorc(Red);
    glBegin(GL_LINES);
    glVertex3f(0,0,0);
    glVertex3f(0.1*e*g,0,0);
    glEnd();
    glColorc(Green);
    glBegin(GL_LINES);
    glVertex3f(0,0,0);
    glVertex3f(0,0.1*e*g,0);
    glEnd();
    glColorc(Blue);
    glBegin(GL_LINES);
    glVertex3f(0,0,0);
    glVertex3f(0,0,0.1*e*g);
    glEnd();

    glLineWidth(2);
}

//---------------------------------------------------------------------------

void __fastcall TFormView::FormMouseMove(TObject *Sender,
        TShiftState Shift, int X, int Y) {
    int dx,dy;
    int k;
    vector n,nplane;
    point i,m,z;
    double v;

    if(Shift.Contains(ssShift))
        v=4;
    else if(Shift.Contains(ssCtrl))
        v=2;
    else
        v=1;

    if(Shift.Contains(ssLeft) ) {
        dx = X-LastMousePos[0];//Negativo mueve a la derecha
        dy = Y-LastMousePos[1];//Negativo mueve a arriba

        //viewer rotation

        if(dx<0)
            a+=v*PI/60;
        else
            a-=v*PI/60;

        if(dy>0) {
            b+=v*PI/60;
        } else {
            b-=v*PI/60;
        }
    }

    LastMousePos[0] = X;
    LastMousePos[1] = Y;
}
//---------------------------------------------------------------------------

void __fastcall TFormView::FormMouseWheelDown(TObject *Sender,
        TShiftState Shift, TPoint &MousePos, bool &Handled) {
    //viewer zoom
    double v;
    if(Shift.Contains(ssShift)) {
        v=4;
    } else if(Shift.Contains(ssCtrl)) {
        v=8;
    } else {
        v=2;
    }
    if(d<100*v*2*g)
        d+=v*2*g*tan(0.5/(v*2))/tan(f/(v*2));
}
//---------------------------------------------------------------------------
void __fastcall TFormView::FormMouseWheelUp(TObject *Sender,
        TShiftState Shift, TPoint &MousePos, bool &Handled) {
//viewer zoom
    double v;
    if(Shift.Contains(ssShift)) {
        v=4;
    } else if(Shift.Contains(ssCtrl)) {
        v=8;
    } else {
        v=2;
    }
    if(d>v*2*g)
        d-=v*2*g*tan(0.5/(v*2))/tan(f/(v*2));   //0.5 is the initial fov
}
//---------------------------------------------------------------------------

void __fastcall TFormView::FormResize(TObject *Sender) {
    //resize OpenGL viewport
    w=ClientWidth;
    h=ClientHeight;
    if(h==0)h=1;
    glViewport(0,0,w,h);
}
//---------------------------------------------------------------------------

void __fastcall TFormView::Timer1Timer(TObject *Sender) {
    float speed=0.1;
    tiempo++;
    distancia=speed*tiempo;
}
//---------------------------------------------------------------------------
inline void __fastcall TFormView::DrawPlane(plane p, int a) {

    int i;
    //inner
    glColorc(p.Color*(1-(p.n*Normal(c-o)*0.2)));
    glBegin(GL_TRIANGLES);
        for(i=0;i<p.NT;i++){
            glVertexp(p.t[i].p0);
            glVertexp(p.t[i].p1);
            glVertexp(p.t[i].p2);}
    glEnd();
//contour
    glColorc(p.Color*0.5);
  	glBegin(GL_LINE_LOOP);
        for(i=0;i<p.NP;i++)
            glVertexp(p.p[i]);
  	glEnd();
}
//-------JFLN  SOY UN GENIO CARAJO JAJAJAJ------------------------------------------------
inline void __fastcall TFormView::DrawVector(point po, vector v, bool d, float modvg, color c)
{
    glColorc(c);
    if(d){//gráfico dinámico del vector
        vector uni;
        double mod;
        uni=Normal(v);
        mod=distancia-modvg;
        v=uni*mod;

        glPushMatrix();
              glTranslatef(v.x+po.x, v.y+po.y, v.z+po.z);
              gluSphere(gluNewQuadric(), .05, 35 , 56);
        glPopMatrix();
    }

    glLineWidth(2);
    glBegin(GL_LINES);
        glVertex3f(po.x,po.y,po.z);
        glVertex3f(v.x+po.x, v.y+po.y, v.z+po.z);
    glEnd();
}


plane __fastcall TFormView::PlaneCopyOldIntoNew(plane_ant pa,plane p){
	int cif=0; //JFLN: Counter for internal FOR

	for(cif=0;cif<MaxNChar+1;cif++) p.Name[cif]=pa.Name[cif];	   	  	//name
	for(cif=0;cif<NB;cif++){
		p.a[cif]=pa.a[cif];												//Absorption [frequency band]
		p.s[cif]=pa.s[cif];												//Scattering [frequency band]
		p.i[cif]=pa.i[cif];												//transmIssion [frequency band]
	}
	for(cif=0;cif<MaxNChar+1;cif++)	p.Material[cif]=pa.Material[cif]; 	//material
	p.Color=pa.Color;       											//color RGB
	p.NP=pa.NP;															//Number of Points
	for(cif=0;cif<p.NP;cif++) p.p[cif]=pa.p[cif]; 						//plane Points
	p.NT=pa.NT;															//Number of Triangles
	for(cif=0;cif<p.NT;cif++) p.t[cif]=pa.t[cif];						//plane Triangles
	p.n=pa.n;															//Normal vector
	p.Group=pa.Group;													//group
	for(cif=0;cif<MaxNChar+1;cif++)	p.Layer[cif]=NULL;					// Layer
	return p;
}

//---------------------------------------------------------------------------

plane_ant __fastcall TFormView::PlaneCopyNewIntoOld(plane p,plane_ant pa){
	int cif=0; //JFLN: Counter for internal FOR
	for(cif=0;cif<MaxNChar+1;cif++) pa.Name[cif]=p.Name[cif];			//name
	for(cif=0;cif<NB;cif++){
		pa.a[cif]=p.a[cif];												//Absorption [frequency band]
		pa.s[cif]=p.s[cif];												//Scattering [frequency band]
		pa.i[cif]=p.i[cif];												//transmIssion [frequency band]
	}
	for(cif=0;cif<MaxNChar+1;cif++) pa.Material[cif]=p.Material[cif]; 	//material
	pa.Color=p.Color;       											//color RGB
	pa.NP=p.NP;		      												//Number of Points
	for(cif=0;cif<p.NP;cif++) pa.p[cif]=p.p[cif]; 						//plane Points
	pa.NT=p.NT;      													//Number of Triangles
	for(cif=0;cif<pa.NT;cif++)
                pa.t[cif]=p.t[cif]; 					//plane Triangles
	pa.n=p.n;        													//Normal vector
	pa.Group=p.Group;         											//group
	//for(cif=0;cif<MaxNChar+1;cif++) p.Layer[cif]=NULL;				// Layer
	return pa;
}

//---------------------------------------------------------------------------
void __fastcall TFormView::ReadRoom(void)
{
	int i;
	//room r;
	r.Clear();
        //r.Init();
        //read planes
	FileRead(FileNumber,(int*)&i,sizeof(int));
	if(i>0){
		r.NewPlanes(i);//JFLN: New Planes for New and Old Version
                for(i=0;i<r.NP;i++){
			if(LoadOldData==true){//JFLN: Load Plane Data Without Layers
				FileRead(FileNumber,(plane_ant*)&r.pa[i],sizeof(plane_ant));
				r.p[i]=PlaneCopyOldIntoNew(r.pa[i],r.p[i]);
			}
			else{
				FileRead(FileNumber,(plane*)&r.p[i],sizeof(plane));
				r.pa[i]=PlaneCopyNewIntoOld(r.p[i],r.pa[i]);
			}
		}
	}
        cuartoCargado=true;
        //assign room
	//FormMain->r=r;
}
//---------------------------------------------------------------------------
void __fastcall TFormView::tlbCargarSalaClick(TObject *Sender)
{
        Timer1->Enabled=false;
        if(OpenDialog1->Execute()){
        FileExtension=ExtractFileExt(OpenDialog1->FileName);
        //check if it's a Raios' file
        FileNumber=FileOpen(OpenDialog1->FileName,fmOpenRead);
        FileRead(FileNumber,(int*)&Version,sizeof(int)); //JFLN: int -> long int
        FileRead(FileNumber,(int*)&FileType,sizeof(int));

        if(Version<RaiosVersion){
            LoadOldData=true;
            SaveOldData=false;
        }
        else {
            LoadOldData=false;
            SaveOldData=false;
        }

        //check if there is any error on file
        if(FileNumber==-1){
            MessageDlg(Message11,mtError,TMsgDlgButtons()<<mbOK,0);
            return;
        }
        //check if it's a Raios' file
        if(FileExtension==".pro"&&FileType!=ProjectFile){
            MessageDlg(Message11,mtError,TMsgDlgButtons()<<mbOK,0);
            return;
        }

        if(FileExtension==".pro"){

            CompleteFileName=OpenDialog1->FileName;
            FileName=ExtractFileName(OpenDialog1->FileName);
            FileName=FileName.SubString(1,FileName.Length()-4);
            Caption=AnsiString("RAIOS - ")+FileName;

            FileRead(FileNumber,(config*)&cfg,sizeof(config));
            a=cfg.a;        //Alpha [horizontal viewer angle]
            b=cfg.b;        //Beta [vertical viewer angle]
            d=cfg.d;        //observer Distance
            f=cfg.f;        //Fov [focus angle]
            g=cfg.g;        //Grig space
            e=cfg.e;        //grid Elements
            c=cfg.c;        //Central point

            ReadRoom();

        }
        //close file
        FileClose(FileNumber);
        }
        
    vector *vet,org;
    org.x=0;
    org.y=0;
    org.z=0;
    vet = new vector[2];
    //-----------RAYO 1---------------------------------------------------------
    vet[0].x=1.2;
    vet[0].y=1;
    vet[0].z=1.6;
    vet[0]=Normal(vet[0]);
    //-----------RAYO 2---------------------------------------------------------
    vet[1].x=1.6;
    vet[1].y=1;
    vet[1].z=1.2;
    vet[1]=Normal(vet[1]);

        int numTri=0;
        triangle *repTri;
        simulacionOctree(); //crea el octree y manda mensaje con total de tringulos de la sala

        repTri=octree.ProcesoRecursivo(org,vet,numTri);
        //ShowMessage("Sumatoria de triangulos en todos los nodos: "+AnsiString(numTri));
        //cuboSala();

}
//---------------------------------------------------------------------------

void __fastcall TFormView::tlbCargarCuboClick(TObject *Sender)
{
    cuartoCargado=true;
    //Inicializaciones cubo
    r.Clear();
    r.NewPlanes(6);
    //-------------square 1 back
    //r.p[0].ID=0;
    //r.p[0].NewPoints(4);
    r.p[0].NP=4;
    r.p[0].p[0].x=-1.0f;
    r.p[0].p[0].y=1.0f;
    r.p[0].p[0].z=1.0f;
    r.p[0].p[1].x=-1.0f;
    r.p[0].p[1].y=-1.0f;
    r.p[0].p[1].z=1.0f;
    r.p[0].p[2].x=-1.0f;
    r.p[0].p[2].y=-1.0f;
    r.p[0].p[2].z=-1.0f;
    r.p[0].p[3].x=-1.0f;
    r.p[0].p[3].y=1.0f;
    r.p[0].p[3].z=-1.0f;
    r.p[0].PointGenTriangle();

    //-------------square 2 front
    //r.p[1].ID=1;
    //r.p[1].NewPoints(4);
    r.p[1].NP=4;
    r.p[1].p[0].x=1.0f;
    r.p[1].p[0].y=1.0f;
    r.p[1].p[0].z=1.0f;
    r.p[1].p[1].x=1.0f;
    r.p[1].p[1].y=1.0f;
    r.p[1].p[1].z=-1.0f;
    r.p[1].p[2].x=1.0f;
    r.p[1].p[2].y=-1.0f;
    r.p[1].p[2].z=-1.0f;
    r.p[1].p[3].x=1.0f;
    r.p[1].p[3].y=-1.0f;
    r.p[1].p[3].z=1.0f;
    r.p[1].PointGenTriangle();

    //-------------square 3 left
    //r.p[2].ID=2;
    //r.p[2].NewPoints(4);
    r.p[2].NP=4;
    r.p[2].p[0].x=-1.0f;
    r.p[2].p[0].y=-1.0f;
    r.p[2].p[0].z=1.0f;
    r.p[2].p[1].x=1.0f;
    r.p[2].p[1].y=-1.0f;
    r.p[2].p[1].z=1.0f;
    r.p[2].p[2].x=1.0f;
    r.p[2].p[2].y=-1.0f;
    r.p[2].p[2].z=-1.0f;
    r.p[2].p[3].x=-1.0f;
    r.p[2].p[3].y=-1.0f;
    r.p[2].p[3].z=-1.0f;
    r.p[2].PointGenTriangle();

    //-------------square 4 right
    //r.p[3].ID=3;
    //r.p[3].NewPoints(4);
    r.p[3].NP=4;
    r.p[3].p[0].x=1.0f;
    r.p[3].p[0].y=1.0f;
    r.p[3].p[0].z=1.0f;
    r.p[3].p[1].x=-1.0f;
    r.p[3].p[1].y=1.0f;
    r.p[3].p[1].z=1.0f;
    r.p[3].p[2].x=-1.0f;
    r.p[3].p[2].y=1.0f;
    r.p[3].p[2].z=-1.0f;
    r.p[3].p[3].x=1.0f;
    r.p[3].p[3].y=1.0f;
    r.p[3].p[3].z=-1.0f;
    r.p[3].PointGenTriangle();

    //-------------square 5 top
    //r.p[4].ID=4;
    //r.p[4].NewPoints(4);
    r.p[4].NP=4;
    r.p[4].p[0].x=-1.0f;
    r.p[4].p[0].y=-1.0f;
    r.p[4].p[0].z=1.0f;
    r.p[4].p[1].x=-1.0f;
    r.p[4].p[1].y=1.0f;
    r.p[4].p[1].z=1.0f;
    r.p[4].p[2].x=1.0f;
    r.p[4].p[2].y=1.0f;
    r.p[4].p[2].z=1.0f;
    r.p[4].p[3].x=1.0f;
    r.p[4].p[3].y=-1.0f;
    r.p[4].p[3].z=1.0f;
    r.p[4].PointGenTriangle();

    //-------------square 1 bottom
    //r.p[5].ID=5;
    //r.p[5].NewPoints(4);
    r.p[5].NP=4;
    r.p[5].p[0].x=-1.0f;
    r.p[5].p[0].y=1.0f;
    r.p[5].p[0].z=-1.0f;
    r.p[5].p[1].x=-1.0f;
    r.p[5].p[1].y=-1.0f;
    r.p[5].p[1].z=-1.0f;
    r.p[5].p[2].x=1.0f;
    r.p[5].p[2].y=-1.0f;
    r.p[5].p[2].z=-1.0f;
    r.p[5].p[3].x=1.0f;
    r.p[5].p[3].y=1.0f;
    r.p[5].p[3].z=-1.0f;
    r.p[5].PointGenTriangle();

    //Inicializar normales de los planos
    // se calculan las normales con la normal de su primer triangulo
    for (int i=0; i<r.NP; i++) {
        r.p[i].n=TriangleNormal(r.p[i].t[0]);
        for (int j=0;j<r.p[i].NT;j++)
            r.p[i].t[j].CalculateProjection();
    }

    simulacionOctree();
    //cuboSala();

}
//---------------------------------------------------------------------------

void __fastcall TFormView::tlbSimulacionClick(TObject *Sender)
{
    tiempo=0;
    distancia=0;

    if (bandSim==false && cuartoCargado){

    // inicializar datos del vector (punto de origen y dirección
    origen.x=0;
    origen.y=0;
    origen.z=0;
    Rays = new vector[2];
    modulo = new float[2];
    //-----------RAYO 1---------------------------------------------------------
    Rays[0].x=1.2;
    Rays[0].y=1;
    Rays[0].z=1.6;
    modulo[0]=Module(Rays[0]);
    Rays[0]=Normal(Rays[0]);
    //-----------RAYO 2---------------------------------------------------------

    Rays[1].x=1.6;
    Rays[1].y=1;
    Rays[1].z=1.2;
    modulo[1]=Module(Rays[1]);
    Rays[1]=Normal(Rays[1]);
    //--------------------------------------------------------------------------

    ry=r.simulation(rc, origen, Rays, vg);
    vec_gra=new vector[ry[0].N-1];
    mod_vg = new float[ry[0].N];
    mod_vg[0]=0;
    int i;

    for ( i=0; i<ry[0].N-1; i++){      //grafica el vector a ser reflectado y luego calcula su módulo
        vec_gra[i]=ry[0].r[i+1].restaPuntos(ry[0].r[i]);
        mod_vg[i+1]=Module(vec_gra[i]);
    }

    for ( i=1; i<ry[0].N; i++){
        mod_vg[i]=mod_vg[i-1]+mod_vg[i];
    }

    vec_gra2=new vector[ry[1].N-1];
    mod_vg2 = new float[ry[1].N];
    mod_vg2[0]=0;

    //Graf the future vector proyection of the ray current
    for (i=0; i<ry[1].N-1; i++){
        vec_gra2[i]=ry[1].r[i+1].restaPuntos(ry[1].r[i]);
        mod_vg2[i+1]=Module(vec_gra2[i]);
    }
    //Calc the module of vector reflection
    for (i=1; i<ry[1].N; i++){
        mod_vg2[i]=mod_vg2[i-1]+mod_vg2[i];
    }
    bandSim=true;
    Timer1->Enabled=true;
    }
    else{
        bandSim=false;
        Timer1->Enabled=false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormView::tlbTrasladarClick(TObject *Sender)
{
        int NT,NP;
        double cordX,cordY,cordZ;
        try{
                cordX=FormView->edtX->Text.ToDouble();
                cordY=FormView->edtY->Text.ToDouble();
                cordZ=FormView->edtZ->Text.ToDouble();

                       for(int PL=0;PL<r.NP;PL++){
                                for(int T=0; T<r.p[PL].NT; T++){
                                        r.p[PL].t[T].p0.x += cordX;
                                        r.p[PL].t[T].p0.y += cordY;
                                        r.p[PL].t[T].p0.z += cordZ;

                                        r.p[PL].t[T].p1.x += cordX;
                                        r.p[PL].t[T].p1.y += cordY;
                                        r.p[PL].t[T].p1.z += cordZ;

                                        r.p[PL].t[T].p2.x += cordX;
                                        r.p[PL].t[T].p2.y += cordY;
                                        r.p[PL].t[T].p2.z += cordZ;
                                }
                                for(int P=0;P<r.p[PL].NP;P++){
                                        r.p[PL].p[P].x += cordX;
                                        r.p[PL].p[P].y += cordY;
                                        r.p[PL].p[P].z += cordZ;

                                }
                        }
                        octree.m_vCenter.x += cordX;
                        octree.m_vCenter.y += cordY;
                        octree.m_vCenter.z += cordZ;
           }
        catch(EConvertError *err){
                ShowMessage("Ingrese las coordenadas de Traslacion");
        }
}

//---------------------------------------------------------------------------
void __fastcall TFormView::simulacionOctree()
{
    if(cuartoCargado){

        int numTriangles=0;
        int nodesCounter=0;
        int endNodeCount=0;
        
        for(int i=0;i<r.NP;i++)  //for every plane
            numTriangles+=r.p[i].NT;
        ShowMessage("Numero de triangulos de la sala: "+AnsiString(numTriangles));
        triangle *triangles = new triangle[numTriangles];
        int index=0;
        
        for(int i=0;i<r.NP;i++)
            for(int j=0;j<r.p[i].NT;j++){
                triangles[index]=r.p[i].t[j];
                index++;
            }

        octree.g_CurrentSubdivision = &nodesCounter;
        octree.g_EndNodeCount= &endNodeCount;
        octree.GetSceneDimensions(triangles,numTriangles);
        octree.createNode(triangles,numTriangles,octree.m_vCenter,octree.m_Width);
        octree.nodeTriangles;

        point vertexMin;
        point vertexMax;
        vector origin;
        vector direction;
        vertexMax.init(octree.m_vCenter.x+(octree.m_Width/2.0f),octree.m_vCenter.y+(octree.m_Width/2.0f),octree.m_vCenter.z+(octree.m_Width/2.0f));
        vertexMin.init(octree.m_vCenter.x-(octree.m_Width/2.0f),octree.m_vCenter.y-(octree.m_Width/2.0f),octree.m_vCenter.z-(octree.m_Width/2.0f));

        Box box(vertexMin,vertexMax);

        ray2.origin.x=0;
        ray2.origin.y=0;
        ray2.origin.z=0;

        ray2.direction.x=0.54;
        ray2.direction.y=0.45;
        ray2.direction.z=0.72;


        origin.init(ray2.origin.x,ray2.origin.y,ray2.origin.z);
        direction.init(ray2.direction.x,ray2.direction.y,ray2.direction.z);

        vector v1,v2,v0;
        float t=0;
        triangle tt;
        float *distance= new float[octree.m_TriangleCount];

        std::ofstream outfile("C:\\Users\\Gadiel\\Desktop\\Datos.txt", std::ofstream::out);
        for (int i = 0; i < octree.m_TriangleCount ; i++){

                v0.init( octree.nodeTriangles[i].p0.x, octree.nodeTriangles[i].p0.y, octree.nodeTriangles[i].p0.z);
                v1.init( octree.nodeTriangles[i].p1.x, octree.nodeTriangles[i].p1.y, octree.nodeTriangles[i].p1.z);
                v2.init( octree.nodeTriangles[i].p2.x, octree.nodeTriangles[i].p2.y, octree.nodeTriangles[i].p2.z);

                float d = octree.rayTriangleIntersect(origin,direction, v0, v1, v2, t);

                outfile <<i<<" \n";
                outfile <<"( "<< octree.nodeTriangles[i].p0.x <<"; "<<octree.nodeTriangles[i].p0.x<<"; "<<octree.nodeTriangles[i].p0.x<<" )\n";
                outfile <<"( "<< octree.nodeTriangles[i].p1.x <<"; "<<octree.nodeTriangles[i].p1.x<<"; "<<octree.nodeTriangles[i].p1.x<<" )\n";
                outfile <<"( "<< octree.nodeTriangles[i].p2.x <<"; "<<octree.nodeTriangles[i].p2.x<<"; "<<octree.nodeTriangles[i].p2.x<<" )\n";

                outfile << d <<" \n \n";

                int argum=0;
        }
        outfile.close();

        Ray ray(origin,direction);
        bool aux=octree.intersect(ray);
        //ry=r.simulationMoller(ray2,triangles,numTriangles);

        delete [] triangles;

        /*vec_gra=new vector[ry[0].N-1];
        mod_vg = new float[ry[0].N];
        mod_vg[0]=0;
        int i;

        for ( i=0; i<ry[0].N; i++){      //grafica el vector a ser reflectado y luego calcula su módulo
                vec_gra[i]=ry[0].r[i].restaPuntos(ry[0].r[i-1]);
                mod_vg[i+1]=Module(vec_gra[i]);
        }

        for ( i=1; i<ry[0].N; i++){
                mod_vg[i]=mod_vg[i-1]+mod_vg[i];
        }

        vec_gra2=new vector[ry[1].N-1];
        mod_vg2 = new float[ry[1].N];
        mod_vg2[0]=0;

        //Graf the future vector proyection of the ray current
        for (i=0; i<ry[1].N; i++){
                vec_gra2[i]=ry[1].r[i+1].restaPuntos(ry[1].r[i]);
                mod_vg2[i+1]=Module(vec_gra2[i]);
        }

        //Calc the module of vector reflection
        for (i=1; i<ry[1].N; i++){
                mod_vg2[i]=mod_vg2[i-1]+mod_vg2[i];
        }

        bandSim=true;
        Timer1->Enabled=true;*/

        }
        else{
                bandSim=false;
                Timer1->Enabled=false;
                ShowMessage("Cuarto no cargado");
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormView::btnPruebaClick(TObject *Sender)
{
             vector origin, direction, v0, v1, v2;
             float t=0;
             origin.init(0,0,0);
             direction.init(0.54,0.45,0.72);
             v0.init(3.01,1.18,4.85);
             v1.init(4.19,8.06,4.85);
             v2.init(4.19,1.18,4.85);
             float distance=octree.rayTriangleIntersect(origin,direction, v0, v1, v2, t);
}
//---------------------------------------------------------------------------

/*void __fastcall TFormView::btnCheckTriangleClick(TObject *Sender)
{

       /* bool checkTri( octree, triangle2 ){

        bool resultado=false;

        for(int k=0; k < octree.m_TriangleCount; k++){
                if(octree.nodeTriangles[k]==(triangle2)){
                        resultado=true;
                }
        }

        if(!resultado){
                for(int l=0; l < 8; l++){
                        if( octree.m_pOctreeNodes[l]!=NULL ){
                                resultado = checkTri( octree.m_pOctreeNodes[l], triangle2);
                                if(resultado==true)
                                        break;
                        }
                }
        }
        return resultado;
        }

        for( int P=0; P < r.NP; P++ ){
                for(int T=0; T<r.p[P].NT; T++){
                        if(checkTri(octree ,r.p[P].t)){
                                ShowMessage("Triángulo no Encontrado");
                        }
                }
        }
};*/
//---------------------------------------------------------------------------

