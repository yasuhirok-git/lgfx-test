#pragma once

#define LGFX_USE_V1

#include <LovyanGFX.hpp>

// RP2040でLovyanGFXを独自設定で利用する場合の設定例

/*
このファイルを複製し、新しい名前を付けて、環境に合わせて設定内容を変更してください。
作成したファイルをユーザープログラムからincludeすることで利用可能になります。

複製したファイルはライブラリのlgfx_userフォルダに置いて利用しても構いませんが、
その場合はライブラリのアップデート時に削除される可能性があるのでご注意ください。

安全に運用したい場合はバックアップを作成しておくか、ユーザープロジェクトのフォルダに置いてください。
//*/


/// 独自の設定を行うクラスを、LGFX_Deviceから派生して作成します。
class LGFX_Raspberry_Pi_Pico_SPI_ILI9341 : public lgfx::LGFX_Device
{
/*
 クラス名は"LGFX"から別の名前に変更しても構いません。
 AUTODETECTと併用する場合は"LGFX"は使用されているため、LGFX以外の名前に変更してください。
 また、複数枚のパネルを同時使用する場合もそれぞれに異なる名前を付けてください。
 ※ クラス名を変更する場合はコンストラクタの名前も併せて同じ名前に変更が必要です。

 名前の付け方は自由に決めて構いませんが、設定が増えた場合を想定し、
 例えばRRaspberry Pi PicoでSPI接続のILI9341の設定を行った場合、
  LGFX_Raspberry_Pi_Pico_SPI_ILI9341
 のような名前にし、ファイル名とクラス名を一致させておくことで、利用時に迷いにくくなります。
//*/


// 接続するパネルの型にあったインスタンスを用意します。
//lgfx::Panel_GC9A01      _panel_instance;
//lgfx::Panel_GDEW0154M09 _panel_instance;
//lgfx::Panel_HX8357B     _panel_instance;
//lgfx::Panel_HX8357D     _panel_instance;
//lgfx::Panel_ILI9163     _panel_instance;
  lgfx::Panel_ILI9341     _panel_instance;
//lgfx::Panel_ILI9342     _panel_instance;
//lgfx::Panel_ILI9481     _panel_instance;
//lgfx::Panel_ILI9486     _panel_instance;
//lgfx::Panel_ILI9488     _panel_instance;
//lgfx::Panel_IT8951      _panel_instance;
//lgfx::Panel_SH110x      _panel_instance; // SH1106, SH1107
//lgfx::Panel_SSD1306     _panel_instance;
//lgfx::Panel_SSD1327     _panel_instance;
//lgfx::Panel_SSD1331     _panel_instance;
//lgfx::Panel_SSD1351     _panel_instance; // SSD1351, SSD1357
//lgfx::Panel_SSD1963     _panel_instance;
//lgfx::Panel_ST7735      _panel_instance;
//lgfx::Panel_ST7735S     _panel_instance;
//lgfx::Panel_ST7789      _panel_instance;
//lgfx::Panel_ST7796      _panel_instance;


// パネルを接続するバスの種類にあったインスタンスを用意します。
  lgfx::Bus_SPI       _bus_instance;   // SPIバスのインスタンス
//lgfx::Bus_I2C       _bus_instance;   // I2Cバスのインスタンス (ESP32のみ)
//lgfx::Bus_Parallel8 _bus_instance;   // 8ビットパラレルバスのインスタンス (ESP32のみ)

public:

  // コンストラクタを作成し、ここで各種設定を行います。
  // クラス名を変更した場合はコンストラクタも同じ名前を指定してください。
  LGFX_Raspberry_Pi_Pico_SPI_ILI9341(void)
  {
    { // バス制御の設定を行います。
      auto cfg = _bus_instance.config();    // バス設定用の構造体を取得します。

// SPIバスの設定
      cfg.spi_host = 1;         // 使用するSPIの番号を指定
      cfg.spi_mode = 0;             // SPI通信モードを設定 (0 ~ 3)
      cfg.freq_write = 10000000;    // 送信時のSPIクロック (最高66.5MHz, 66.5MHzを整数で割った値に丸められます)
      cfg.freq_read  =  6666666;    // 受信時のSPIクロック
      cfg.pin_sclk =  10; // SPIのSCLKピン番号を設定
      cfg.pin_mosi =  11; // SPIのMOSIピン番号を設定
      cfg.pin_miso =  -1; // SPIのMISOピン番号を設定 (-1 = disable)
      cfg.pin_dc   =  15; // SPIのD/Cピン番号を設定  (-1 = disable)
     // SDカードと共通のSPIバスを使う場合、MISOは省略せず必ず設定してください。

// ※ ピン番号の設定は、Arduino互換用のピン番号ではなく、"PA07" 等の実際のMCUのポート番号を指定します。
// ※ SERCOMのPAD設定は不要です。LGFX内部でSERCOM番号とポート番号を元にPADを自動設定する仕組みになっています。
//*/
/*
// I2Cバスの設定
      cfg.i2c _index = 0;         // 使用するI2Cの番号を指定
      cfg.freq_write  = 400000;     // 送信時のクロック
      cfg.freq_read   = 400000;     // 受信時のクロック
      cfg.pin_sda =  8; // I2CのSDAをピン番号を設定
      cfg.pin_scl =  9; // I2CのSCLをピン番号を設定
      cfg.i2c_addr    = 0x3C;       // I2Cデバイスのアドレス
//*/

      _bus_instance.config(cfg);    // 設定値をバスに反映します。
      _panel_instance.setBus(&_bus_instance);      // バスをパネルにセットします。
    }

    { // 表示パネル制御の設定を行います。
      auto cfg = _panel_instance.config();    // 表示パネル設定用の構造体を取得します。

      cfg.pin_cs   =  13; // CSが接続されているピン番号   (-1 = disable)
      cfg.pin_rst  =  14; // RSTが接続されているピン番号  (-1 = disable)
      cfg.pin_busy =    -1;  // BUSYが接続されているピン番号 (-1 = disable)

      // ※ 以下の設定値はパネル毎に一般的な初期値が設定されていますので、不明な項目はコメントアウトして試してみてください。

      cfg.memory_width     =   240;  // ドライバICがサポートしている最大の幅
      cfg.memory_height    =   320;  // ドライバICがサポートしている最大の高さ
      cfg.panel_width      =   240;  // 実際に表示可能な幅
      cfg.panel_height     =   320;  // 実際に表示可能な高さ
      cfg.offset_x         =     0;  // パネルのX方向オフセット量
      cfg.offset_y         =     0;  // パネルのY方向オフセット量
      cfg.offset_rotation  =     0;  // 回転方向の値のオフセット 0~7 (4~7は上下反転)
      cfg.dummy_read_pixel =     8;  // ピクセル読出し前のダミーリードのビット数
      cfg.dummy_read_bits  =     1;  // ピクセル以外のデータ読出し前のダミーリードのビット数
      cfg.readable         =  true;  // データ読出しが可能な場合 trueに設定
      cfg.invert           = false;  // パネルの明暗が反転してしまう場合 trueに設定
      cfg.rgb_order        = false;  // パネルの赤と青が入れ替わってしまう場合 trueに設定
      cfg.dlen_16bit       = false;  // データ長を16bit単位で送信するパネルの場合 trueに設定
      cfg.bus_shared       =  true;  // SDカードとバスを共有している場合 trueに設定(drawJpgFile等でバス制御を行います)

      _panel_instance.config(cfg);
    }

    setPanel(&_panel_instance); // 使用するパネルをセットします。
  }
};