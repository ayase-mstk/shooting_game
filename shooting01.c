/********************************/
/*  シューティングゲーム        */
/*                              */
/*                              */
/*  キャラクター     W : 敵     */
/*                   A : 自分   */
/*                              */
/*  操作                        */
/*   ←→矢印 : 左右に移動      */
/*   ↑矢印   : ビームを発射    */
/*                              */
/*                              */
/*             ゲーム終了 : ESC */
/********************************/
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<windows.h>

#define XMAX 80
#define YMAX 24

void main ()
{
  char buf[YMAX][XMAX]; //character array field
  int xW=30, yW=0;      //character W position
  int dxW=1;            //character W amount of move
  int xWb, yWb=YMAX;    //W's beam position
  int xA=40,yA=YMAX-1;  //character A position
  int xAb,yAb=-1;       //character A amount of move
  int i,j;              //character array key

  while(1)
  {
    system("cls");                      //window delete

    memset(&buf[0][0],' ', XMAX*YMAX);  //character array clear
    buf[yW][xW]='W';                    //M placement
    buf[yA][xA]='A';                    //A placement
    if (yWb<YMAX) buf[yWb][xWb]='$';     //$ placement
    if (yAb>=0 ) buf[yAb][xAb]='|';     //| placement

    for(i=0;i<YMAX;i++) {
      printf("%.*s",XMAX,&buf[i][0]);   //display one sentence print
    }
    fflush(stdout);

    if (xW==xAb && yW==yAb) {           //W と |の位置が重なったら終了
      Beep(784, 1000);
      break;
    }
    if (xA==xWb && yA==yWb) {           //A と $の位置が重なったら終了
      Beep(330, 1000);
      break;
    }
    if (xAb==xWb && abs(yAb-yWb)<=1) {  //| と $の位置が重なったら消滅
      Beep(588, 100);
      yAb=-1;
      yWb=YMAX;
    }

    if (xW==0 || xW==79) dxW=-dxW;       //Wの方向が左右両端で反転
    xW+=dxW;                            //Wの一更新
    if (yWb<YMAX) yWb+=1;               //$が一番下に行くまで1進む
    if (yAb>=0) yAb-=1;                 //|が一番上に行くまで1進む

    if (kbhit( ) != 0) {                 //キーコードがおされたら
      j=getch( );                        //入力を受け取り
      if(j==27) break;                  //ESCキーを押したら終了
      if(j==0) j=getch( );               //特殊キー
      if(j==75){                        //←
        xA-=3;
        if(xA<0) xA=0;
      }else if (j==77){                 //→
        xA+=3;
        if(xA>=XMAX) xA=XMAX-1;
      }
      if (j==72 && yAb<0) {             //|がなければ↑で|発射
        xAb=xA;
        yAb=yA-1;
      }
    }
    if (xA==xW && yWb>=YMAX) {          //WとAの縦位置一緒で$無いと$発射
      xWb=xW;
      yWb=1;
    }
    Sleep(50);                          //0.5秒ごとに動く
  }
}