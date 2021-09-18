#include <iostream>
#include <math.h>
#include <string>
#include <fstream>
#include <time.h>
#include <cstdlib>
#define MIN(x,y) ((x) < (y) ? (x) : (y)) 
using namespace std;
struct node {
    string data;
    node* next;
};
void arama(string deneme)
{
    srand(time(NULL));
    node* r;
    r = NULL;
    int i, j, l1, l2, t, track;
    int dist[50][50];
    char s1[50], s2[50];
    ifstream dosyaOku("kelime.txt");
    int deger = 0;
    string deneme2;
    int basla = clock();
    if (dosyaOku.is_open())
    {
        for (i = 0; i < deneme.length(); i++)
        {
            s1[i] = deneme[i];//karakter karakter alıyoruz
        }
        while (getline(dosyaOku, deneme2))
        {
            for (int l = 0; l < deneme2.length(); l++)
            {
                s2[l] = deneme2[l];//karakter karakter alıyoruz
            }
            l1 = deneme.length();
            l2 = deneme2.length();
            for (i = 0; i <= l1; i++)
            {
                dist[0][i] = i;//matris oluşturuyoruz algoritma gereği
            }
            for (j = 0; j <= l2; j++)
            {
                dist[j][0] = j;//matris oluşturuyoruz algoritma gereği
            }
            for (j = 1; j <= l1; j++)
            {
                for (i = 1; i <= l2; i++)
                {
                    if (s1[i - 1] == s2[j - 1])
                    {
                        track = 0;
                    }
                    else
                    {
                        track = 1;
                    }
                    t = MIN((dist[i - 1][j] + 1), (dist[i][j - 1] + 1));
                    dist[i][j] = MIN(t, (dist[i - 1][j - 1] + track));
                }
            }
            if (dist[l2][l1] < 2)//uzaklığı 2'den küçük olanları alıyoruz
            {
                if (dist[l2][l1] == 0)//eğer 0'a eşit olursa kelime bulunmuş demektir
                {
                    deger++;
                    break;//aranılan kelime bulunduğu için ve dosyamız da sözlük olduğundan burada kesmek mantıklı olur çünkü zaten aynı kelimeden sözlükte başka olmaz istersek kaldırabiliriz ve komple hepsinde aramasını sağlayabiliriz 
                }
                else
                {
                    if (r == NULL)
                    {
                        r = new node;
                        r->data = deneme2;
                        r->next = NULL;
                    }
                    else
                    {
                        node* yrd;
                        yrd = r;
                        while (yrd->next != NULL)
                            yrd = yrd->next;
                        yrd->next = new node;
                        yrd->next->data = deneme2;
                        yrd->next->next = NULL;
                        yrd = NULL;
                        delete yrd;
                    }
                }
            }
            for (int l = 0; l < 50; l++)
            {
                s2[l] = 0;//eğer aktardıklarımızı silmezsek kelime uzunluğu farkından sorunlar oluşabilir
            }
        }
        if (deger == 0)//eğer değer 0'a eşitse hiç aynı kelimeden yok demektir 
        {
            
            if(r == NULL)
            {
            cout << "aradiginiz bulunamadi" << endl;
            int bitir = clock();
            cout << "islem suresi: " << (float)(bitir - basla) / CLOCKS_PER_SEC << " saniye" << endl;
	    }
	    else
	    {
		ofstream dosyanin("bir.txt");
		cout << "bunu mu demek istediniz" << endl;
		while (r != NULL)
                {
                dosyanin << r->data << endl;//çıkan değerleri başka bir txt ye kaydediyoruz
                cout << r->data << endl;
                r = r->next;
                }               
                int bitir = clock();
                cout << "islem suresi: " << (float)(bitir - basla) / CLOCKS_PER_SEC << " saniye" << endl;
            	dosyanin << "islem suresi: " << (float)(bitir - basla) / CLOCKS_PER_SEC << " saniye" << endl;
            	cout << "sonuclar txt basilmistir" << endl;
            	dosyanin.close();
            	system("start bir.txt");//sonuçları yazılı olan txt'yi açmak için
	      }
        }
        else
        {
            ofstream dosyanin("bir.txt");
            cout << "aradiginiz bulunmustur" << endl;
            dosyanin << deneme << endl;
            cout << deneme << endl;
            int bitir = clock();
            cout << "islem suresi: " << (float)(bitir - basla) / CLOCKS_PER_SEC << " saniye" << endl;
            dosyanin << "islem suresi: " << (float)(bitir - basla) / CLOCKS_PER_SEC << " saniye" << endl;
            dosyanin.close();
            cout << "sonuclar txt basilmistir" << endl;
            system("start bir.txt");//sonuÃ§larÄ± yazÄ±lan txt dosyasini ekrana Ã§Ä±karÄ±r
        }
        dosyaOku.close();
    }
    else
    {
        cout << "dosya hatasi" << endl;
    }
}

int main()
{  
    string cindeger;
    cout << "Aramak istediginiz kelimeyi yaziniz" << endl;
    cin >> cindeger;
    cout << ".txt dosyasinda araniyor.." << endl;
    arama(cindeger);
    system("pause");
}
