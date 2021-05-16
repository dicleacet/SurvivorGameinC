#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
int *Engelmetre;

struct ParkurYapimi
{
int ParkurUzunlugu;
int EngelSayisi;
int HP;
};

void Parkur()
{
    int *Pu,*Es,i,j;
    srand(time(NULL));
    struct ParkurYapimi py;
    py.HP = 100;
    Pu = &py.ParkurUzunlugu;
    Es = &py.EngelSayisi;
    *Pu = 50+rand()%51;
    *Es = 2+rand()%4;
    Engelmetre = (int *) calloc(*Es,sizeof(int));
    for(i=0;i<*Es;i++){
    *(Engelmetre+i) = 5+rand()%(*Pu-4);
    if(i!=0)
    for (j=0;j<i;++j) {
            if(*(Engelmetre+j)==*(Engelmetre+i))i--;}
    }
     for (i=0;i<(*Es-1);i++)
        for (j=0;j<*Es-i-1;j++)
            if(*(Engelmetre+j)>*(Engelmetre+(j+1)))
            {
                int Gecici=*(Engelmetre+j);
                *(Engelmetre+j)=*(Engelmetre+(j+1));
                *(Engelmetre+(j+1))=Gecici;
                }
}

bool AsalMi(int i,int hp)
{
    int KucukSayi,s,j;
    bool Asal;
    s=0;
    if(hp<*(Engelmetre+i)) KucukSayi=hp;
    else KucukSayi=*(Engelmetre+i);
    for(j=2;j<=KucukSayi;j++){
    if(hp%j==0 && *(Engelmetre+i)%j==0) s=1;
}
if (s==0) Asal = true;
else Asal = false;
    return Asal;
}

void Yarisma()
{
    FILE *Paryap;
    Paryap = fopen("Log.txt","w+");
    if(Paryap == NULL)
        {
            printf("Error opening file !\n");
            exit(1);
        }
    fprintf(Paryap,"Yarisma Basladi !!!\n");
    int i,*Es,hp;
    bool As;
    struct ParkurYapimi py;
    hp = py.HP;
    Es = &py.EngelSayisi;
    for(i=0;i<*Es;i++)
    {
        fprintf(Paryap,"Yarismaci HP = %d\n",hp);
        fprintf(Paryap,"Yarismaci %d. metreye kadar bir engelle karsilasmadi.\n",*(Engelmetre+i));
        As = AsalMi(i,hp);
        if(As == true){
            fprintf(Paryap,"%d. metrede bir engel var. %d ve %d aralarinda asaldir.\n",Engelmetre[i],hp,Engelmetre[i]);
            hp -= *(Engelmetre+i);}
        else
            fprintf(Paryap,"%d. metrede bir engel var. %d ve %d aralarinda asal degildir.\n",*(Engelmetre+i),hp,*(Engelmetre+i));}
    if(hp<=0)
        fprintf(Paryap,"Uzgunum !!! Yarismayi tamamlayamadin.\n");
    else
        fprintf(Paryap,"Tebrikler !!! Yarismayi %d HP ile bitirdiniz.\n",hp);
        printf("Yarisma Tamamlandi !");
}

int main()
{
    Parkur();
    Yarisma();
    return 0;
}
