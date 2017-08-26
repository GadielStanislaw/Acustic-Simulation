//---------------------------------------------------------------------------
#ifndef DefinitionsH
#define DefinitionsH
//---------------------------------------------------------------------------
#define None                    -1
//Key operation--------------------------------------------------------------
#define ViewerRotate            0
#define ViewerMove              1
#define ViewerZoom              2
#define ViewerPerspective       3
#define ViewerGridElements      4
#define ViewerGridSpace         5
//Mouse operation------------------------------------------------------------
#define CreatePlane             0
#define CreatePlaneNormal       1
#define CreateSource            2
#define CreateReceiver          3
#define CreateAudience          4
#define CreateAudienceTarget    5
#define ObjectsSelect           6
#define ObjectsMove             7
#define ObjectsRotate           8
//#define ObjectsDelete         9
#define ObjectsCopy             10
#define ViewerCenter            11
#define ViewerMRotate           12 //JFLN: Mouse Operation for Rotate Viewer 20090916
#define ViewerMMove             13 //JFLN: Mouse Operation for Move Viewer 20090916
#define ViewerMZoom             14 //JFLN: Mouse Operation for Zoom Viewer 20090916
#define ViewerMPerspective      15 //JFLN: Mouse Operation for Perspective Viewer 20090916
#define ViewerMGridElements     16 //JFLN: Mouse Operation for changing number of GridElements 20090917
#define ViewerMGridSpace        17 //JFLN: Mouse Operation for changing GridSpace size 20090917
//Projection-----------------------------------------------------------------
#define xy                      0
#define xz                      1
#define yz                      2
//Constants------------------------------------------------------------------
#define PI                      3.1415926535897932384626433832795
#define Rho                     1.204
#define NB                      6       //Number of frequency Bands
#define NB2                     9       //Number of frequency Bands
#define NG                      4       //Number of Graphs
#define MaxNPoints              200     //maximum Number of points // en promedio un rayo se refleja 50 veces 
#define MaxNPointsAnt           30      //maximum Number of points 
#define MaxNSelectedPlanes      2000    //1000//maximum Number of selected planes
#define MaxNSelectedSources     2000    //maximum Number of selected planes
#define MaxNSelectedReceivers   2000    //maximum Number of selected planes
#define MaxNChar                50      //maximum Number of characteres
#define MaxNAngles              13      //13 subdivisões em um arco de PI rad. 15° de discretização.
#define MaxAbsorption           2.0     //maximum value for absorption coefficients
#define MaxScattering           1.0     //maximum value for scattering coefficients
#define MaxTransmission         1.0     //maximum value for transmission coefficients
#define VViewDivision           0.7     //ClientArea Vertical division
#define HViewDivision           0.5     //ClientArea Horizontal division
#define ElemFrmWidth            300     //JFLN: FormElements Width for other Form's Width definition 18092009
#define ToolBarHeight           38      //JFLN: FormMain ToolBar Height
#define SpaceforSB              4       //JFLN: Horizontal and Vertical Space when Scroll Bar is present 18092009
#define MaxDIR                  300     //Max Directory length
#define MaxSRays                1002    //Number of Rays for preview
//Quality Acoustics Parameters-----------------------------------------------
#define QapT30                     0
#define QapEDT                     1
#define QapD50                     2
#define QapD80                     3
#define QapC50                     4
#define QapC80                     5
#define QapTS                      6
#define QapG                       7
#define QapLG                      8
#define QapLF                      9
#define QapLFC                     10
#define QapSTI                     11
//Material Details-----------------------------------------------------------
#define CharOfAbs01             "Low frequency absorbent."
#define CharOfAbs02             "Wide band absorbent."
#define CharOfAbs03             "Resonance absorbent."
#define CharOfAbs04             "High frequency absorbent."
#define CharOfAbs05             "Poor absorbent."
#define MatCriter01             "Mineral / rock wool / high absorbent".
#define MatCriter02             "Gypsum, plaster."
#define MatCriter03             "Wooden plates, chipboard."
#define MatCriter04             "Glass."
#define MatCriter05             "Metal."
#define MatCriter06             "Stone, brick, concrete, clinker."
#define MatCriter07             "Foam rubber  (hard / soft foam, polystyrol, polystyrene,) rubber."
#define MatCriter08             "Synthetic material, linoleum, hard plastics."
#define MatCriter09             "Tissues, carpets, textiles."
#define MatCriter10             "Paper, cardboard."
#define MatCriter11             "Audiences."
#define MatCriter12             "Miscellaneous."
#define SurfSuita01             "Suitable for gyms, (ball games)."
#define SurfSuita02             "Suitable for paint over."
#define SurfSuita03             "Waterproof, moisture resistant, washable."
#define SurfSuita04             "Heat resistant, fireproof (to various degrees)."
//Messages-------------------------------------------------------------------
#define Message01               "String cannot exceed 50 characters."
#define Message02               "Point is identical to its antecessor."
#define Message03               "Select at least one plane."
#define Message04               "Point outside of plane."
#define Message05               "Invalid floating point value."
#define Message06               "Feature not available yet."
#define Message07               "Select at least one object."
#define Message08               "Select one source and at least one plane."
#define Message09               "This is not a RAIOS valid file."
#define Message10               "No project file associated. Please, save as *.pro."
#define Message11               "Cannot open this file."
#define Message12               "File already exists. Overwrite it?"
#define Message13               "Please, save your work if you didn't.\nDo you really want to close RAIOS?"
#define Message14               "Insufficient memory! Please, try to low down one or several of the following parameters:\n  Impulse response discretization\n  Surface discretization\n  Stop decay"
#define Message15               "There is no active source"
#define Message16               "There is no active receiver"
#define Message17               "There is no valid surface.\nAll octave bands must have absorption coefficients greater than zero."
#define Message18               "There are apertures in the room\nPlease, close spaces with valid surfaces or with completely absorbing  planes, if you are representing an open space."
#define Message18J              "There are too many lost rays. Continue?"
#define Message19               "Feature not available.\n"
#define Message20               "RAIOS was unable to load the ray's file.\nPlease, run the room simulation project."
#define Message21               "You must choose an anechoic signal in order to run the auralization process."
#define Message22               "Please, select one source."
#define Message23               "Please, select one receiver."
#define Message24               "RAIOS was unable to load the room simulation project data."
#define Message25               "Do you want to save the current project?"
#define Message26               "Are you sure you want to delete all selected objects?"
#define Message27               "Error: RAOIS attempted to perform an illegal mathematical operation.\nMake sure that all data parameters are valid."
#define Message28               "Please, open a project file first."
#define Message29               "Please, execute and save the room simulation."
#define Message30               "Error: Missing file. Reinstall RAIOS or contact your software dealer."
#define Message31               "Warning: More than one dongle detected."
#define Message32               "Warning: Unable to open dongle. Contact your software dealer."
#define Message33               "Warning: Please, keep the dongle inserted to your computer."
#define Message34               "Warning: Unable to complete dongle's security check procedure. Contact your software dealer."
#define Message35               "Warning: Unable read dongle security code. Contact your software dealer."
#define Message36               "Warning: The security code of inserted dongle does not match your software copy. Contact your software dealer."
#define Message37               "RAIOS 5.0 Demo Mode Activated."
#define Message38               "Please, choose one of the pre-designed room projects (*.pro).\n"
#define Message39               "Cleaning the working area"
#define Message40               "RAIOS v5.0\nWith Auralization"
#define Message41               " "
//Codes----------------------------------------------------------------------
#define RaiosVersion            13600 //inverse date int(021106)=8774 //JFLN: 13600 Raios Version (max 32767)
#define ProjectFile             1
#define RoomFile                2
#define SurfaceFile             3
#define MaterialFile            4
#define DirectivityFile         5
#define MaterialDBFile          6
//---------------------------------------------------------------------------
#endif
