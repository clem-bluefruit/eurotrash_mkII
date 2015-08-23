/*
*
* display update routines
*
*/

/* --------------------- display simple message --------------------- */

void _display(char *_disp) 
{
  u8g_FirstPage(&u8g);
  do {
        u8g_DrawStr(&u8g, 5, 15, _disp);
        u8g_DrawLine(&u8g, 0, 25, 120, 25);
       
 
    } while(u8g_NextPage(&u8g)); 
} 
   
/* --------------------- display simple message --------------------- */

void _display_num(int16_t _num) 
{
  char _disp[0x6];
  sprintf(_disp, "%d", _num);
  
  u8g_FirstPage(&u8g);
  do {
        u8g_DrawStr(&u8g, 5, 15, _disp);
        u8g_DrawLine(&u8g, 0, 25, 120, 25);
       
    } while(u8g_NextPage(&u8g)); 
} 
   
/* --------------------- draw main menu ----------------------------- */

void _do_display()
{
  _REDRAW = 0x0; 
  
  int16_t srt, eof, _bank, _sel, _ch;
  char s[0x6], e[0x6], _dis[0x8];
  
  _ch = _ACTIVE_CHANNEL; 
  srt   = audioChannels[_ch]->enc0;
  eof   = audioChannels[_ch]->encX;
  _bank = audioChannels[_ch]->bank;
  // channel ? bank ? 
  _sel = _bank ? _ch + 0x2 : _ch; 
  
  // make things printable
  sprintf(s, "%d",srt);
  sprintf(e, "%d",eof);
  memcpy(_dis, _thebanks[_sel], 0x8);
  
  switch (_MENU_PAGE[_ACTIVE_CHANNEL]) { 
     
     case FILESELECT: {
        u8g_FirstPage(&u8g);
        do {
            // cursor 
            u8g_DrawBox(&u8g, 0, 4, 129, 16);    
            u8g_SetDefaultBackgroundColor(&u8g);  
            // filename    
            u8g_DrawStr(&u8g, 5, 15, _dis);
            u8g_DrawStr(&u8g, 65, 15, _display_file);
            u8g_SetDefaultForegroundColor(&u8g);
            //
            u8g_DrawLine(&u8g, 0, 25, 129, 25); 
            // start
            u8g_DrawStr(&u8g, 5, 45, "srt pos: ");
            u8g_DrawStr(&u8g, 100, 45, s);
            // eof
            u8g_DrawStr(&u8g, 5, 60, "end pos: ");
            u8g_DrawStr(&u8g, 100, 60, e);
            
        } while(u8g_NextPage(&u8g)); 
        break;  
     }
     case STARTPOS:  {
        u8g_FirstPage(&u8g);
        do {  
            // filename  
            u8g_DrawStr(&u8g, 5, 15, _dis);
            u8g_DrawStr(&u8g, 65, 15, _display_file);
            //
            u8g_DrawLine(&u8g, 0, 25, 129, 25); 
            // cursor 
            u8g_DrawBox(&u8g, 0, 34, 129, 16); 
            u8g_SetDefaultBackgroundColor(&u8g);
            // start
            u8g_DrawStr(&u8g, 5, 45, "srt pos: ");
            u8g_DrawStr(&u8g, 100, 45, s);
            u8g_SetDefaultForegroundColor(&u8g);
            // eof
            u8g_DrawStr(&u8g, 5, 60, "end pos: ");
            u8g_DrawStr(&u8g, 100, 60, e);
            
        } while(u8g_NextPage(&u8g)); 
        break;  
     }
     case ENDPOS:  {
        u8g_FirstPage(&u8g);
        do {
            // filename
            u8g_DrawStr(&u8g, 5, 15, _dis);
            u8g_DrawStr(&u8g, 65, 15, _display_file);
            //
            u8g_DrawLine(&u8g, 0, 25, 129, 25); 
            // start
            u8g_DrawStr(&u8g, 5, 45, "srt pos: ");
            u8g_DrawStr(&u8g, 100, 45, s);
            // cursor
            u8g_DrawBox(&u8g, 0, 50, 129, 16);    
            u8g_SetDefaultBackgroundColor(&u8g); 
            // eof
            u8g_DrawStr(&u8g, 5, 60, "end pos: ");
            u8g_DrawStr(&u8g, 100, 60, e);
            u8g_SetDefaultForegroundColor(&u8g);
            
        } while(u8g_NextPage(&u8g)); 
        break;  
     }
    }
} 

/* ----------------------- init display --------------------------- */

void init_display() 
{ 
    uint16_t _file, _bank;
   
    _file = audioChannels[_ACTIVE_CHANNEL]->file_wav; 
    _bank = audioChannels[_ACTIVE_CHANNEL]->bank;
    
    _display_file[0x0] = '\xb7';
    memcpy(_display_file+0x2, DISPLAYFILES[_file + _bank*MAXFILES], DISPLAY_LEN);
    _REDRAW = 0x1;
}

/* ------------------------ splash --------------------------------- */

void _hello() 
{  
    u8g_SetFont(&u8g, u8g_font_6x12);
    u8g_SetColorIndex(&u8g, 1);
  
    u8g_FirstPage(&u8g);
    do {
        u8g_DrawLine(&u8g, 5, 25, 120, 25);
        u8g_DrawStr(&u8g, 5, 45, "eurotrash mkII");
    } while(u8g_NextPage(&u8g)); 
}
     
/* ----------------------------------------------------------------- */

void _display_calibration() 
{
  char _disp0[0x6], _disp1[0x6], _disp2[0x6], _disp3[0x6];
  
  sprintf(_disp0, "%d", _MIDPOINT[0]);
  sprintf(_disp1, "%d", _MIDPOINT[1]);
  sprintf(_disp2, "%d", _MIDPOINT[2]);
  sprintf(_disp3, "%d", _MIDPOINT[3]);
  
  u8g_FirstPage(&u8g);
  do {
         u8g_DrawStr(&u8g, 0, 8,  "ok? - push top button");
         u8g_DrawLine(&u8g, 0, 13, 120, 13);
         
         u8g_DrawStr(&u8g, 5, 25, "L - srt");
         u8g_DrawStr(&u8g, 80, 25, _disp0);
         
         u8g_DrawStr(&u8g, 5, 35, "L - eof");
         u8g_DrawStr(&u8g, 80, 35, _disp1);
         
         u8g_DrawStr(&u8g, 5, 45, "R - srt");
         u8g_DrawStr(&u8g, 80, 45, _disp2);
         
         u8g_DrawStr(&u8g, 5, 55, "R - eof");
         u8g_DrawStr(&u8g, 80, 55, _disp3);
         
    } while(u8g_NextPage(&u8g)); 
} 