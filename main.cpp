#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
using namespace sf;
using namespace std;

int x = 100, y = 100, h = 200; // x, y la toa do cua nhan vat, h la gioi han do cao
float vx = 0, vy = 0; // vx, vy la toc do di chuyen ngang,doc
int score=0;

struct point
{
    int x,y;
};

void StartGame()
{
    RenderWindow window(VideoMode(400,533), "Doodle jump", Style::Close);
    Texture t;
    t.loadFromFile("startgame.jpg");
    Sprite sStartgame(t);
    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed) exit(0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) exit(0);
        if (Keyboard::isKeyPressed(Keyboard::Space))
        {
            window.close();
        }
        window.draw(sStartgame);
        window.display();
    }
}

void GameOver()
{
    RenderWindow window(VideoMode(400, 533), "Doodle jump", Style::Close);
    Texture t;
    t.loadFromFile("gameover.jpg");
    Sprite sGameover(t);
    system("cls");
    cout << "Your score is: " << score/100 << endl; // hien thi diem khi game over

    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed) exit(0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) exit(0); // an ESC thi thoat game
        if (Keyboard::isKeyPressed(Keyboard::Space)) // an space thi choi tiep, dat lai vi tri cua nhan vat va diem so
        {
            x = 100; y = 100;
            vx = 0; vy = 0;
            score = 0;
            window.close();
        }
        window.draw(sGameover);
        window.display();
    }
}

int main()
{
    StartGame();
    RenderWindow window(VideoMode(400, 533), "Doodle jump", Style::Close);
    window.setFramerateLimit(50);

    Texture t1,t2,t3;
    t1.loadFromFile("background.jpg");
    t2.loadFromFile("bar.png");
    t3.loadFromFile("doodle.png");

    Sprite sBackground(t1), sBar(t2), sPerson(t3);

    point bar[20];

    SoundBuffer S1,S2;
    S1.loadFromFile("Die.wav");
    S2.loadFromFile("Point.wav");
    Sound sound1(S1), sound2(S2);

    // Dat vi tri random cho 10 thanh
    for (int i=0;i<10;i++)
      {
       bar[i].x = rand()%400;
       bar[i].y = rand()%533;
      }

    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed) window.close();
        }

        // Di chuyen nhan vat
        if (Keyboard::isKeyPressed(Keyboard::Right)) x+=3;
        if (Keyboard::isKeyPressed(Keyboard::Left)) x-=3;

        // Tao ra trong luc keo nhan vat xuong
        vy+=0.2; // gia toc 0.2 thi voi moi giay roi xuong se nhanh hon
        y+=vy; // thay doi vi tri y cua nhan vat dua vao van toc vy

        if (y > 533) // neu nhan vat roi ra khoi man hinh thi game over
        {
            sound1.play();
            GameOver();
        }

        if (y < h) // khi nhan vat bay den gioi han h thi thay vi cho nhan vat bay len tiep thi se cho cac thanh ngang di xuong
            for (int i=0;i<10;i++)
            {
                y=h; // giu nguyen vi tri nhan vat o gioi han
                bar[i].y=bar[i].y-vy; // cho thanh ngang đi chuyen xuong voi van toc bang vat toc bay len của nhan vat
                score+=abs(vy);
                if (bar[i].y>533) // neu thanh ngang di xuong khoi man hinh thi tao lai thanh ngang day o tren dau man hinh
                {
                    bar[i].x=rand()%400;
                    bar[i].y=0;
                }
            }

        // Xet va cham cua nhan vat voi thanh
        for (int i=0;i<10;i++)
            if ((x+30>bar[i].x-34) && (x-10<bar[i].x+34) // kiem tra chan nhan vat co nam trong pham vi thanh ngang hay khong
            && (y+70>bar[i].y) && (y+70<bar[i].y+14) && (vy>0)) // kiem tra chan nhan vat co cham vao thanh ngang theo phuong di xuong ko
            {
                sound2.play();
                vy=-10;
            }

        sPerson.setPosition(x,y); //cap nhat vi tri nhan vat
        window.draw(sBackground);
        window.draw(sPerson);
        for (int i=0;i<10;i++)
        {
            sBar.setPosition(bar[i].x,bar[i].y);
            window.draw(sBar);
        }

        window.display();
    }

    return 0;
}
