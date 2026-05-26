#include"function.h"

  int noteIndex = 0; //現在の音符ポインタ
  unsigned long t_next = 0; //次の拍の予測絶対時間
  const uint8_t sendTime = 0; //シリアル通信を行う時間
  bool beatUpdated = false; //拍予測の更新
  enum State {IDLE , CALIBRATE , PREBEAT , PLAYING , TEMPO_CHANGE , FERMATA };
  State state =IDLE; //現在の状態
  uint8_t note_off = 1; //前の音の終了
  uint8_t note = 0; //音名インデックス（休符＝２５５）
  uint8_t vel = 0; //音の強さ（0~127）

  const uint8_t score[][2] ={
    {0, 100},
    {1, 100},
    {2, 100}
  };

  const int SCORE_LEN = sizeof ( score ) / sizeof ( score[0]);


void setup() {
  Serial.begin(9600);

  Serial.print("Note_OFF");
  Serial.print(",");
  Serial.print("NOTE");
  Serial.print(",");
  Serial.println("VEL");
}


void loop() {
  if (state != FERMATA) {
    if(noteIndex <= SCORE_LEN){

      if (beatUpdated == true) {
        sendTime = sendTime_set(t_next);

        note = score[noteIndex][0];
        vel  = score[noteIndex][1];
        
         if (millis() >= sendTime){
           Serial.print(note_off);
           Serial.print(",");
           Serial.print(note);
           Serial.print(",");
           Serial.println(vel);

           noteIndex++;
           beatUpdated = false;

        }
      
      }
    }
  }
 
}
