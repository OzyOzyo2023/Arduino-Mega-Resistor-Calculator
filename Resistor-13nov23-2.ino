// Resistor 13nov23-2 am probleme cand colorez benzile colorate pe resistor , nu sta pe
//banda 1 , si se  coloreaza toate
// 13nov23 ora 24 , inca nu am reusit  sa  colores o singura banda ,se coloreaza toate 3

#include <TouchScreen.h> //touch library
  #include <LCDWIKI_GUI.h> //Core graphics library
    #include <LCDWIKI_KBV.h> //Hardware-specific library
    
         #include <SPI.h>
            #include <Wire.h>
        
LCDWIKI_KBV mylcd(ILI9341,A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset
//---------------touch code------------- luat din touch_pen example---------

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

//param calibration from kbv
#define TS_MINX 911
#define TS_MAXX 117

#define TS_MINY 87
#define TS_MAXY 906

#define STATUS_X 10
#define STATUS_Y 65

//touch sensitivity for press
#define MINPRESSURE 10
#define MAXPRESSURE 1000
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
#define AQUA2    0x04FF
#define GRAY2    0x8410
#define  BROWN1  8B4513
#define   BROWN2  A0522D
#define  BROWN3    A52A2A 
#define   MARUN2   800000 
#define   ORANGE2  FFA500
#define BLACK 0x0000
#define WHITE 0xFFFF
#define GRAY 0x7BEF
#define LT_GREY 0xC618
#define GREEN 0x07E0
#define LIME 0x87E0
#define BLUE 0x001F
#define RED 0xF800
#define AQUA 0x5D1C
#define YELLOW 0xFFE0
#define MAGENTA 0xF81F
#define CYAN 0x07FF
#define DK_CYAN 0x03EF
#define ORANGE 0xFCA0
#define PINK 0xF97F
#define BROWN 0x8200
#define VIOLET 0x9199
#define SILVER 0xA510
#define GOLD 0xA508
#define NAVY 0x000F
#define MAROON 0x7800
#define PURPLE 0x780F
#define OLIVE 0x7BE0


//--------------------------------------------------------------
int banda;
int box;
int setTouch=0;
int xval;
int yval;
//-------------benzile colorate---------------
 int tura1=1;
 int tura2=1;
 int tura3=1;
//-------------boxele colorate----------------
int turaC0=1;
int turaC1=1;
int turaC2=1;
int turaC3=1;
int turaC4=1;
int turaC5=1;
int turaC6=1;
int turaC7=1;
int turaC8=1;
int turaC9=1;

void setup() 

{
  
  Serial.begin(9600);
   mylcd.Init_LCD();
  Serial.println(mylcd.Read_ID(), HEX);
  mylcd.Fill_Screen(BLACK);
 mylcd.Set_Rotation(3); 
//--------box 1 ---------------------------------------
mylcd.Set_Text_Mode(0);
 mylcd.Set_Draw_color(YELLOW);
//------------------------------------
mylcd.Set_Draw_color(GRAY);
mylcd.Fill_Circle(53, 59, 30);
 mylcd.Fill_Circle(250, 59, 30);
  mylcd.Fill_Round_Rectangle(68, 35, 235, 85,5);  //------------dreptunghi intre cercuri
   mylcd.Set_Draw_color(CYAN);
    mylcd.Fill_Round_Rectangle(5, 55, 23, 64,5);  //--------------sarma stanga
     mylcd.Fill_Round_Rectangle(280, 55, 298, 64,5);  //--------------sarma dreapta

mylcd.Set_Draw_color(RED);
 mylcd.Fill_Round_Rectangle(43, 30, 63, 90,5);  //-------------- banda 1
   mylcd.Set_Draw_color(GREEN);
    mylcd.Fill_Round_Rectangle(93, 35, 113, 85,5);  //-------------- banda 2
     mylcd.Set_Draw_color(BLUE);
      mylcd.Fill_Round_Rectangle(143, 35, 163, 85,5);  //-------------- banda 3
       mylcd.Set_Draw_color(YELLOW);
        mylcd.Fill_Round_Rectangle(215, 35, 235, 85,5);  //-------------- banda 4


  mylcd.Set_Draw_color(BLACK);
   mylcd.Fill_Round_Rectangle(3, 110, 22, 150,5);
   mylcd.Set_Draw_color(WHITE);
 //   mylcd.Draw_Round_Rectangle(3, 110, 22, 150,5); // fac rama alba in juru culori negre
   mylcd.Draw_Round_Rectangle(2, 109, 23, 151,5); // fac rama alba in juru culori negre
    mylcd.Set_Draw_color(MAROON);
     mylcd.Fill_Round_Rectangle(32, 110, 54, 150,5);
      mylcd.Set_Draw_color(RED);
       mylcd.Fill_Round_Rectangle(64, 110, 86, 150,5); 
        mylcd.Set_Draw_color(ORANGE);
         mylcd.Fill_Round_Rectangle(96, 110, 118, 150,5);
          mylcd.Set_Draw_color(YELLOW);
           mylcd.Fill_Round_Rectangle(128, 110, 150, 150,5);
             mylcd.Set_Draw_color(GREEN);
              mylcd.Fill_Round_Rectangle(160, 110, 182, 150,5);
               mylcd.Set_Draw_color(BLUE);
                mylcd.Fill_Round_Rectangle(192, 110, 214, 150,5);
                 mylcd.Set_Draw_color(VIOLET);
                  mylcd.Fill_Round_Rectangle(224, 110, 246, 150,5);
                   mylcd.Set_Draw_color(GRAY);
                    mylcd.Fill_Round_Rectangle(256, 110, 278, 150,5);
                     mylcd.Set_Draw_color(WHITE);
                      mylcd.Fill_Round_Rectangle(288, 110, 310, 150,5);

    mylcd.Set_Text_colour(GREEN);
 mylcd.Set_Text_Back_colour(BLACK); 
 mylcd.Set_Text_Size(2);
 mylcd.Print_String("Calculator", 95, 10);
mylcd.Set_Text_colour(GREEN);
   mylcd.Set_Text_Size(3);
   mylcd.Print_String("band ", 30, 170);
   mylcd.Print_String("box  ", 180, 170);
 
}

void loop() 
{
readTouchPen();

}   
 //-----------------------------------------

void readTouchPen ()
{
 if (setTouch<10) {
 TSPoint p = ts.getPoint();  // citeste touch pen
 pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
   
  //----------------citim unde Touch cu Penu ----------------------
  
  if (p.z > 10 && p.z < 1000)      // daca apesi destul de tare
  {
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, mylcd.Get_Display_Width());  // pen poz pe X
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, mylcd.Get_Display_Height()); // pen poz pe Y
    xval=p.x;
    yval=p.y;
    //-------------------------------------------------------
    
    
   //--------------- aici verific ce am apasat , box si banda  -------------


 //-----------------------banda 1-----------------------------
 if (tura1<10) 
 {  
if((xval >= 34) && (xval <= 115)) {
if ((yval >= 190) && (yval <= 207));{
  banda=1;  // aici rezultatu de la banda
  tura1=20;  // rezultatu de la tura
  
}
}
} 

//-------------------------banda 2------------------------------
if (tura2<10) 
 {  
if((xval >= 43) && (xval <= 103)) {
 if ((yval >= 153) && (yval <= 172)) {
  banda=2;
  tura2=20;
 
}
}
}
 
//--------------------------banda 3-------------------------------

if (tura3<10)
{
if((xval >= 41) && (xval <= 105))  {
if ((yval >= 113) && (yval <= 131)) {
 banda=3;
 tura3=20;
 
} 
 }
}


//-----------------aici bag color Boxes----------------------------
if (turaC0<10)  // Black
{
if ((xval >= 145) && (xval <=200))  {
if ((yval >= 222) && (yval <= 235))  {
box=0;
turaC0=20;
if ((banda=1)&& (tura1=20))  {
  mylcd.Set_Draw_color(BLACK);
 mylcd.Fill_Round_Rectangle(43, 30, 63, 90,5);  //-banda 1 
}

 if ((banda=2)&&(tura2=20)) {
   mylcd.Set_Draw_color(BLACK);
    mylcd.Fill_Round_Rectangle(93, 35, 113, 85,5);  
 }
if ((banda=3)&&(tura3=20)) { 
  mylcd.Set_Draw_color(BLACK);
      mylcd.Fill_Round_Rectangle(143, 35, 163, 85,5);
  
}
}
}
 }

 //--------------------------------------------------------------  
 if (turaC1<10) // MAROON
{   
if((xval >= 145) && (xval <= 200)) {
if ((yval >= 196) && (yval <= 216)){
box=1;
turaC1=20;
if (banda=1){
  mylcd.Set_Draw_color(MAROON);
 mylcd.Fill_Round_Rectangle(43, 30, 63, 90,5);  //-banda 1 
}
 if (banda=2){
   mylcd.Set_Draw_color(MAROON);
    mylcd.Fill_Round_Rectangle(93, 35, 113, 85,5);  
 }
if (banda=3){ 
  mylcd.Set_Draw_color(MAROON);
      mylcd.Fill_Round_Rectangle(143, 35, 163, 85,5);
  
}
}
}
 } 
 

//----------------------------------------------------------------
if (turaC2<10)  // RED
{
if((xval >= 145) && (xval <= 200)) {
if ((yval >= 174) && (yval <= 192)) {
box=2;
turaC2=20;
if (banda=1){
  mylcd.Set_Draw_color(RED);
 mylcd.Fill_Round_Rectangle(43, 30, 63, 90,5);  //-banda 1 
}
 if (banda=2){
   mylcd.Set_Draw_color(RED);
    mylcd.Fill_Round_Rectangle(93, 35, 113, 85,5);  
 }
if (banda=3){ 
  mylcd.Set_Draw_color(RED);
      mylcd.Fill_Round_Rectangle(143, 35, 163, 85,5);
  
}
}
}
 }

//-----------------------------------------------------------------
if (turaC3<10) //ORANGE
{
if((xval >= 145) && (xval <= 200))   {
if ((yval >= 147) && (yval <= 168))  {
box=3;
turaC3=20;
if (banda=1){
  mylcd.Set_Draw_color(ORANGE);
 mylcd.Fill_Round_Rectangle(43, 30, 63, 90,5);  //-banda 1 
}
 if (banda=2){
   mylcd.Set_Draw_color(ORANGE);
    mylcd.Fill_Round_Rectangle(93, 35, 113, 85,5);  
 }
if (banda=3){ 
  mylcd.Set_Draw_color(ORANGE);
      mylcd.Fill_Round_Rectangle(143, 35, 163, 85,5);
  
}
}
}
 }

//------------------------------------------------------------------
if (turaC4<10)  //YELLOW
{
if((xval >= 145) && (xval <= 200))  { 
if ((yval >= 123) && (yval <= 140))  {
box=4;
turaC4=20;
if (banda=1){
  mylcd.Set_Draw_color(YELLOW);
 mylcd.Fill_Round_Rectangle(43, 30, 63, 90,5);  //-banda 1 
}
 if (banda=2){
   mylcd.Set_Draw_color(YELLOW);
    mylcd.Fill_Round_Rectangle(93, 35, 113, 85,5);  
 }
if (banda=3){ 
  mylcd.Set_Draw_color(YELLOW);
      mylcd.Fill_Round_Rectangle(143, 35, 163, 85,5);
  
}
}
}
 }

//--------------------------------------------------------------------
if (turaC5<10)     // GREEN
{
if ((xval >= 145) && (xval <= 200))   {
if ((yval >= 96) && (yval <= 116))  {
box=5;
turaC5=20;
if (banda=1){
  mylcd.Set_Draw_color(GREEN);
 mylcd.Fill_Round_Rectangle(43, 30, 63, 90,5);  //-banda 1 
}
 if (banda=2){
   mylcd.Set_Draw_color(GREEN);
    mylcd.Fill_Round_Rectangle(93, 35, 113, 85,5);  
 }
if (banda=3){ 
  mylcd.Set_Draw_color(GREEN);
      mylcd.Fill_Round_Rectangle(143, 35, 163, 85,5);
  
}
}
}
 }

//--------------------------------------------------------------------
if (turaC6<10)  //BLUE
{
if((xval >= 145) && (xval <= 200))  {
if((yval >= 73) && (yval <= 91))   {
box=6;
turaC6=20;
if (banda=1){
  mylcd.Set_Draw_color(BLUE);
 mylcd.Fill_Round_Rectangle(43, 30, 63, 90,5);  //-banda 1 
}
 if (banda=2){
   mylcd.Set_Draw_color(BLUE);
    mylcd.Fill_Round_Rectangle(93, 35, 113, 85,5);  
 }
if (banda=3){ 
  mylcd.Set_Draw_color(BLUE);
      mylcd.Fill_Round_Rectangle(143, 35, 163, 85,5);
  
}
}
}
 }

//--------------------------------------------------------------------
if (turaC7<10)  // violet
{
if ((xval >= 145) && (xval <= 200))  {
if ((yval >= 48) && (yval <= 65))   {
box=7;
turaC7=20;
if (banda=1){
  mylcd.Set_Draw_color(VIOLET);
 mylcd.Fill_Round_Rectangle(43, 30, 63, 90,5);  //-banda 1 
}
 if (banda=2){
   mylcd.Set_Draw_color(VIOLET);
    mylcd.Fill_Round_Rectangle(93, 35, 113, 85,5);  
 }
if (banda=3){ 
  mylcd.Set_Draw_color(VIOLET);
      mylcd.Fill_Round_Rectangle(143, 35, 163, 85,5);
  
}
}
}
 }

//--------------------------------------------------------------------
if (turaC8<10)//grey
{
if((xval >= 145) && (xval <= 200))  {
if ((yval >= 25) && (yval <= 42))   {
box=8;
turaC8=20;
if (banda=1){
  mylcd.Set_Draw_color(GRAY);
 mylcd.Fill_Round_Rectangle(43, 30, 63, 90,5);  //-banda 1 
}
 if (banda=2){
   mylcd.Set_Draw_color(GRAY);
    mylcd.Fill_Round_Rectangle(93, 35, 113, 85,5);  
 }
if (banda=3){ 
  mylcd.Set_Draw_color(GRAY);
      mylcd.Fill_Round_Rectangle(143, 35, 163, 85,5);
  
}
}
}
 }

//-----------------------------------------------------------------------
if (turaC9<10)  // white
{
if((xval >= 145) && (xval <= 200))  {
if ((yval >= 1) && (yval <= 17))  {
box=9;
turaC9=20;
if (banda=1){
  mylcd.Set_Draw_color(WHITE);
 mylcd.Fill_Round_Rectangle(43, 30, 63, 90,5);  //-banda 1 
}
 if (banda=2){
   mylcd.Set_Draw_color(WHITE);
    mylcd.Fill_Round_Rectangle(93, 35, 113, 85,5);  
 }
if (banda=3){ 
  mylcd.Set_Draw_color(WHITE);
      mylcd.Fill_Round_Rectangle(143, 35, 163, 85,5);
  
}
}
}
 }
   
 //-------------------sterge cu black box-----------------
  mylcd.Set_Draw_color(BLACK);
   mylcd.Fill_Round_Rectangle(230, 200, 319, 235,5);// pt y
   
 mylcd.Set_Draw_color(BLACK);
   mylcd.Fill_Round_Rectangle(100, 200, 150, 235,5);// pt x
 
   
mylcd.Set_Text_colour(YELLOW);

mylcd.Print_Number_Int(xval,110,200, 0, ' ', 10);
mylcd.Print_Number_Int(yval, 240,200, 0, ' ', 10);

mylcd.Print_Number_Int(banda,110,170, 0, ' ', 10);
 mylcd.Set_Text_colour(BLUE);
mylcd.Print_Number_Int(box, 250,170, 0, ' ', 10); 
//-------------reset benzile----------
tura1=1;
tura2=1;
tura3=1;
//------------reset boxes-------------
turaC0=1;
turaC1=1;
turaC2=1;
turaC3=1;
turaC4=1;
turaC5=1;
turaC6=1;
turaC7=1;
turaC8=1;
turaC9=1;

}   
 }
}   // end touch

void  goOut()
{
  mylcd.Set_Text_colour(GREEN);
   mylcd.Set_Text_Size(3);
   mylcd.Print_String("goOut", 30, 180); 
  delay(3000);
}
