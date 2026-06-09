#include<Arduino.h>

  int noteIndex = 0; //現在の音符ポインタ
  unsigned long t_next = 0; //次の拍の予測絶対時間
  uint8_t sendTime = 0; //シリアル通信を行う時間
  bool beatUpdated = false; //拍予測の更新
  enum State {IDLE , PREBEAT , PLAYING , TEMPO_CHANGE , FERMATA };
  State state =IDLE; //現在の状態
  uint8_t note_off = 1; //前の音の終了
  uint8_t note = 0; //音名インデックス（休符＝２５５）
  uint8_t vel = 0; //音の強さ（0~127）
  const uint8_t score[][2] ={
    {0, 100},//ド　
    {1, 100},//レ
    {2, 100},//ミ
    {3, 100},//ファ｜
    {2, 100},//ミ　
    {1, 100},//レ
    {0, 100},//ド｜
    {2, 127},//ミ
    {3, 127},//ファ
    {4, 127},//ソ
    {5, 127},//ラ｜
    {4, 127},//ソ
    {3, 127},//ファ
    {2, 127},//ミ｜
    {0, 90},//ド
    {0, 90},//ド｜
    {0, 90},//ド
    {0, 90},//ド｜
    {0, 100},//ド
    {0, 100},//ド
    {1, 100},//レ
    {1, 100},//レ
    {2, 100},//ミ
    {2, 100},//ミ
    {3, 100},//ファ
    {3, 100},//ファ｜
    {2, 100},//ミ
    {1, 100},//レ
    {0, 100}//ド
  };
  const int SCORE_LEN = sizeof ( score ) / sizeof ( score[0]);

  unsigned long sendTime_set(unsigned long t_next) {//担当Bよりより出された次の拍の予測絶対時間に補正値をかける
  unsigned long sendTime = t_next;

  return sendTime;

}


void setup() {
  Serial.begin(115200);

  //Serial.print("Note_OFF");
  //Serial.print(",");
  //Serial.print("NOTE");
  //Serial.print(",");
  //Serial.println("VEL");
}


void loop() {
  if (state != FERMATA) {
    if(noteIndex <= SCORE_LEN){

      if (beatUpdated == true) {
        sendTime = sendTime_set(t_next);

        note = score[noteIndex][0];
        vel  = score[noteIndex][1];
        
         if (millis() >= sendTime){
           Serial.write(note_off);
           Serial.write(note);
           Serial.write(vel);

           //Serial.print(note_off);
           //Serial.print(",");
           //Serial.print(note);
           //Serial.print(",");
           //Serial.println(vel);

           noteIndex++;
           beatUpdated = false;

        }
      
      }
    }
  }
 
}
