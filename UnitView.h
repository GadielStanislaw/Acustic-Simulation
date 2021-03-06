//---------------------------------------------------------------------------

#ifndef UnitViewH
#define UnitViewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ExtCtrls.hpp"
#include "MathFunctions.h"
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TFormView : public TForm
{
__published:	// IDE-managed Components
        TTimer *Timer1;
        TOpenDialog *OpenDialog1;
        TToolBar *ToolBar1;
        TToolButton *ToolButton1;
        TToolButton *tlbCargarSala;
        TToolButton *tlbCargarCubo;
        TToolButton *tlbSimulacion;
        TToolButton *ToolButton5;
        TToolButton *tlbTrasladar;
        TLabel *Label1;
        TEdit *edtX;
        TLabel *Label2;
        TEdit *edtY;
        TLabel *Label3;
        TEdit *edtZ;
        TPanel *Panel1;
        TImageList *ImageList1;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TButton *btnPrueba;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    void __fastcall FormMouseWheelDown(TObject *Sender, TShiftState Shift,
          TPoint &MousePos, bool &Handled);
    void __fastcall FormMouseWheelUp(TObject *Sender, TShiftState Shift,
          TPoint &MousePos, bool &Handled);
    void __fastcall FormResize(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall tlbCargarSalaClick(TObject *Sender);
        void __fastcall tlbCargarCuboClick(TObject *Sender);
        void __fastcall tlbSimulacionClick(TObject *Sender);
        void __fastcall tlbTrasladarClick(TObject *Sender);
        void __fastcall btnPruebaClick(TObject *Sender);
        //void __fastcall btnCheckTriangleClick(TObject *Sender);
private:	// User declarations
    HDC     hdc;
    HGLRC   hrc;
    int     PixelFormat;
public:		// User declarations

    __fastcall TFormView(TComponent* Owner);
    void __fastcall SetPixelFormatDescriptor(void);
    void __fastcall IdleLoop(TObject*, bool&);
    void __fastcall glVertexp(point p);
    void __fastcall glColorc(color c);
    void __fastcall DrawScene(void);
    void __fastcall DrawGrid(void);
    void __fastcall DrawCoordinate(point p,color c);
    void __fastcall DrawPoint(point p,color c);
    void __fastcall DrawAxis(void);
    void __fastcall DrawPlane(plane p, int a);
    void __fastcall simulacion();
    void __fastcall ReadRoom(void);
    //void __fastcall cuboSala();
    plane __fastcall PlaneCopyOldIntoNew(plane_ant,plane);
    plane_ant __fastcall PlaneCopyNewIntoOld(plane p,plane_ant pa);
    void __fastcall DrawVector(point po, vector v, bool d, float mod, color c);
    void __fastcall simulacionOctree();
    void __fastcall drawBoundingBox(point m_vCenter,float m_Width);

    bool      Z;                                        //Z operation
    int       h,                                        //window Height
              w,                                        //window Width
              TessTrianglePoint,                        //tesselation triangle point counter
              NGroups,                                  //Number of groups
              NPoints;                                  //Number of points

    config    cfg;
    double    a,                                        //Alpha [horizontal viewer angle]
              b,                                        //Beta [vertical viewer angle]
              d,                                        //observer Distance
              f,                                        //Fov [focus angle]
              g,                                        //Grig space
              e;                                        //grid Elements
    point     c,                                        //Central point
              o;                                        //Observer point
    vector    u,                                        //Unitary vector [mouse application]
              Up;                                       //up vector for OpenGL viewport
    point     SphereFace[32][4];                        //sphere faces
    color     Red,                                      //red default color
              Blue,                                     //blue default color
              Green,                                    //green default color
              Yellow,                                   //yellow default color
              LightGray,                                //lightgray default color
              DarkGray,
              Black;
    int       MouseOperation,
              LastMousePos[2];
    room      r;                                        //Cubic Room
    vector    vg;
    reflection *ry;
    receiver rc;
    vector *vec_gra;
    float *mod_vg;
    vector *vec_gra2;
    float *mod_vg2;

    //Variables of select room
    AnsiString  CompleteFileName,
                FileExtension,
                FileName;
                
    int         FileNumber,
                Version,
                FileType;

    double tiempo,distancia;
    //Datos vectores constructor
    vector *Rays;
    point origen;
    float *modulo;
    bool cuartoCargado,bandSim,LoadOldData,SaveOldData;
    Octree octree;
    Octree octree2[7];
    point pO;
    Ray ray2;
    triangle triangle2;
};
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
extern PACKAGE TFormView *FormView;
//---------------------------------------------------------------------------
#endif
