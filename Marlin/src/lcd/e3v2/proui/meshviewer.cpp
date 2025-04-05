/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2021 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

/**
 * Mesh Viewer for PRO UI
<<<<<<< HEAD
 * Author: Miguel A. Risco-Castillo (MRISCOC)
 * version: 3.14.1
 * Date: 2022/04/11
=======
 * Based on the original work of: Miguel Risco-Castillo (MRISCOC)
 * https://github.com/mriscoc/Ender3V2S1
 * version: 4.2.1
 * Date: 2023/05/05
>>>>>>> origin/release-2.1.3-beta2
 */

#include "../../../inc/MarlinConfigPre.h"

<<<<<<< HEAD
#if BOTH(DWIN_LCD_PROUI, HAS_MESH)

#include "../../../core/types.h"
#include "../../marlinui.h"
#include "dwin_lcd.h"
#include "dwinui.h"
=======
#if ALL(DWIN_LCD_PROUI, HAS_MESH)

#include "../../../core/types.h"
#include "../../marlinui.h"
>>>>>>> origin/release-2.1.3-beta2
#include "dwin.h"
#include "dwin_popup.h"
#include "../../../feature/bedlevel/bedlevel.h"
#include "meshviewer.h"

<<<<<<< HEAD
#if ENABLED(AUTO_BED_LEVELING_UBL)
  #include "bedlevel_tools.h"
#endif

MeshViewerClass MeshViewer;

void MeshViewerClass::DrawMesh(bed_mesh_t zval, const uint8_t sizex, const uint8_t sizey) {
  const int8_t mx = 25, my = 25;  // Margins
  const int16_t stx = (DWIN_WIDTH - 2 * mx) / (sizex - 1),  // Steps
                sty = (DWIN_WIDTH - 2 * my) / (sizey - 1);
  const int8_t rmax = _MIN(mx - 2, stx / 2);
  const int8_t rmin = 7;
  int16_t zmesh[sizex][sizey];
  #define px(xp) (mx + (xp) * stx)
  #define py(yp) (30 + DWIN_WIDTH - my - (yp) * sty)
  #define rm(z) ((z - minz) * (rmax - rmin) / _MAX(1, (maxz - minz)) + rmin)
  #define DrawMeshValue(xp, yp, zv) DWINUI::Draw_Signed_Float(font6x12, 1, 2, px(xp) - 18, py(yp) - 6, zv)
  #define DrawMeshHLine(yp) DWIN_Draw_HLine(HMI_data.SplitLine_Color, px(0), py(yp), DWIN_WIDTH - 2 * mx)
  #define DrawMeshVLine(xp) DWIN_Draw_VLine(HMI_data.SplitLine_Color, px(xp), py(sizey - 1), DWIN_WIDTH - 2 * my)
  int16_t maxz =-32000; int16_t minz = 32000;
  LOOP_L_N(y, sizey) LOOP_L_N(x, sizex) {
    const float v = isnan(zval[x][y]) ? 0 : round(zval[x][y] * 100);
    zmesh[x][y] = v;
    NOLESS(maxz, v);
    NOMORE(minz, v);
  }
  max = (float)maxz / 100;
  min = (float)minz / 100;
  DWINUI::ClearMainArea();
  DWIN_Draw_Rectangle(0, HMI_data.SplitLine_Color, px(0), py(0), px(sizex - 1), py(sizey - 1));
  LOOP_S_L_N(x, 1, sizex - 1) DrawMeshVLine(x);
  LOOP_S_L_N(y, 1, sizey - 1) DrawMeshHLine(y);
  LOOP_L_N(y, sizey) {
    hal.watchdog_refresh();
    LOOP_L_N(x, sizex) {
      uint16_t color = DWINUI::RainbowInt(zmesh[x][y], _MIN(-5, minz), _MAX(5, maxz));
      uint8_t radius = rm(zmesh[x][y]);
      DWINUI::Draw_FillCircle(color, px(x), py(y), radius);
      if (sizex < 9) {
        if (zmesh[x][y] == 0) DWINUI::Draw_Float(font6x12, 1, 2, px(x) - 12, py(y) - 6, 0);
        else DWINUI::Draw_Signed_Float(font6x12, 1, 2, px(x) - 18, py(y) - 6, zval[x][y]);
      }
      else {
        char str_1[9];
        str_1[0] = 0;
        switch (zmesh[x][y]) {
          case -999 ... -100:
            DWINUI::Draw_Signed_Float(font6x12, 1, 1, px(x) - 18, py(y) - 6, zval[x][y]);
            break;
          case -99 ... -1:
            sprintf_P(str_1, PSTR("-.%02i"), -zmesh[x][y]);
            break;
          case 0:
            DWIN_Draw_String(false, font6x12, DWINUI::textcolor, DWINUI::backcolor, px(x) - 4, py(y) - 6, "0");
            break;
          case 1 ... 99:
            sprintf_P(str_1, PSTR(".%02i"), zmesh[x][y]);
            break;
          case 100 ... 999:
            DWINUI::Draw_Signed_Float(font6x12, 1, 1, px(x) - 18, py(y) - 6, zval[x][y]);
            break;
        }
        if (str_1[0])
          DWIN_Draw_String(false, font6x12, DWINUI::textcolor, DWINUI::backcolor, px(x) - 12, py(y) - 6, str_1);
      }
    }
  }
}

void MeshViewerClass::Draw(bool withsave /*= false*/) {
  Title.ShowCaption(GET_TEXT_F(MSG_MESH_VIEWER));
  #if USE_UBL_VIEWER
    DWINUI::ClearMainArea();
    BedLevelTools.viewer_print_value = true;
    BedLevelTools.Draw_Bed_Mesh(-1, 1, 8, 10 + TITLE_HEIGHT);
  #else
    DrawMesh(bedlevel.z_values, GRID_MAX_POINTS_X, GRID_MAX_POINTS_Y);
  #endif
  if (withsave) {
    DWINUI::Draw_Button(BTN_Save, 26, 305);
    DWINUI::Draw_Button(BTN_Continue, 146, 305);
    Draw_Select_Highlight(HMI_flag.select_flag, 305);
  }
  else
    DWINUI::Draw_Button(BTN_Continue, 86, 305);

  #if USE_UBL_VIEWER
    BedLevelTools.Set_Mesh_Viewer_Status();
  #else
    char str_1[6], str_2[6] = "";
    ui.status_printf(0, F("Mesh minZ: %s, maxZ: %s"),
      dtostrf(min, 1, 2, str_1),
      dtostrf(max, 1, 2, str_2)
    );
  #endif
}

void Draw_MeshViewer() { MeshViewer.Draw(true); }
void onClick_MeshViewer() { if (HMI_flag.select_flag) SaveMesh(); HMI_ReturnScreen(); }
void Goto_MeshViewer() { if (leveling_is_valid()) Goto_Popup(Draw_MeshViewer, onClick_MeshViewer); else HMI_ReturnScreen(); }
=======
#if ENABLED(USE_GRID_MESHVIEWER)
  #include "bedlevel_tools.h"
#endif

bool meshredraw;                            // Redraw mesh points
uint8_t sizex, sizey;                       // Mesh XY size
uint8_t rmax;                               // Maximum radius
#define margin 25                           // XY Margins
#define rmin 5                              // Minimum radius
#define zmin -20                            // rmin at z=-0.20
#define zmax  20                            // rmax at z= 0.20
#define width DWIN_WIDTH - 2 * margin
#define r(z) ((z - zmin) * (rmax - rmin) / (zmax - zmin) + rmin)
#define px(xp) (margin + (xp) * (width) / (sizex - 1))
#define py(yp) (30 + DWIN_WIDTH - margin - (yp) * (width) / (sizey - 1))

constexpr uint8_t meshfont = TERN(TJC_DISPLAY, font8x16, font6x12);

MeshViewer meshViewer;

float MeshViewer::max, MeshViewer::min;

void MeshViewer::drawMeshGrid(const uint8_t csizex, const uint8_t csizey) {
  sizex = csizex;
  sizey = csizey;
  rmax = _MIN(margin - 2, 0.5 * (width) / (sizex - 1));
  min = 100;
  max = -100;
  DWINUI::clearMainArea();
  dwinDrawRectangle(0, hmiData.colorSplitLine, px(0), py(0), px(sizex - 1), py(sizey - 1));
  for (uint8_t x = 1; x < sizex - 1; ++x) dwinDrawVLine(hmiData.colorSplitLine, px(x), py(sizey - 1), width);
  for (uint8_t y = 1; y < sizey - 1; ++y) dwinDrawHLine(hmiData.colorSplitLine, px(0), py(y), width);
}

void MeshViewer::drawMeshPoint(const uint8_t x, const uint8_t y, const float z) {
  const uint8_t fs = DWINUI::fontWidth(meshfont);
  const int16_t v = isnan(z) ? 0 : round(z * 100);
  NOLESS(max, z); NOMORE(min, z);

  const uint16_t color = DWINUI::rainbowInt(v, zmin, zmax);
  DWINUI::drawFillCircle(color, px(x), py(y), r(_MAX(_MIN(v, zmax), zmin)));
  TERN_(TJC_DISPLAY, delay(100));

  const uint16_t fy = py(y) - fs;
  if (sizex < TERN(TJC_DISPLAY, 8, 9)) {
    if (v == 0) DWINUI::drawFloat(meshfont, 1, 2, px(x) - 2 * fs, fy, 0);
    else DWINUI::drawSignedFloat(meshfont, 1, 2, px(x) - 3 * fs, fy, z);
  }
  else {
    char msg[9]; msg[0] = '\0';
    switch (v) {
      case -999 ... -100:
      case  100 ...  999: DWINUI::drawSignedFloat(meshfont, 1, 1, px(x) - 3 * fs, fy, z); break;
      case  -99 ...   -1: sprintf_P(msg, PSTR("-.%2i"), -v); break;
      case    1 ...   99: sprintf_P(msg, PSTR( ".%2i"),  v); break;
      default:
        dwinDrawString(false, meshfont, DWINUI::textColor, DWINUI::backColor, px(x) - 4, fy, "0");
        return;
    }
    dwinDrawString(false, meshfont, DWINUI::textColor, DWINUI::backColor, px(x) - 2 * fs, fy, msg);
  }
}

void MeshViewer::drawMesh(const bed_mesh_t zval, const uint8_t csizex, const uint8_t csizey) {
  drawMeshGrid(csizex, csizey);
  for (uint8_t y = 0; y < csizey; ++y) {
    hal.watchdog_refresh();
    for (uint8_t x = 0; x < csizex; ++x) drawMeshPoint(x, y, zval[x][y]);
  }
}

void MeshViewer::draw(const bool withsave/*=false*/, const bool redraw/*=true*/) {
  title.showCaption(GET_TEXT_F(MSG_MESH_VIEWER));
  #if ENABLED(USE_GRID_MESHVIEWER)
    DWINUI::clearMainArea();
    bedLevelTools.viewer_print_value = true;
    bedLevelTools.drawBedMesh(-1, 1, 8, 10 + TITLE_HEIGHT);
  #else
    if (redraw) drawMesh(bedlevel.z_values, GRID_MAX_POINTS_X, GRID_MAX_POINTS_Y);
    else DWINUI::drawBox(1, hmiData.colorBackground, { 89, 305, 99, 38 });
  #endif
  if (withsave) {
    DWINUI::drawButton(BTN_Save, 26, 305);
    DWINUI::drawButton(BTN_Continue, 146, 305);
    drawSelectHighlight(hmiFlag.select_flag, 305);
  }
  else
    DWINUI::drawButton(BTN_Continue, 86, 305);

  #if ENABLED(USE_GRID_MESHVIEWER)
    bedLevelTools.setMeshViewerStatus();
  #else
    char str_1[6], str_2[6] = "";
    ui.status_printf(0, F("Mesh minZ: %s, maxZ: %s"), dtostrf(min, 1, 2, str_1), dtostrf(max, 1, 2, str_2));
  #endif
}

void drawMeshViewer() { meshViewer.draw(true, meshredraw); }

void onClick_MeshViewer() { if (hmiFlag.select_flag) saveMesh(); hmiReturnScreen(); }

void gotoMeshViewer(const bool redraw) {
  meshredraw = redraw;
  if (leveling_is_valid()) gotoPopup(drawMeshViewer, onClick_MeshViewer);
  else hmiReturnScreen();
}
>>>>>>> origin/release-2.1.3-beta2

#endif // DWIN_LCD_PROUI && HAS_MESH
