/* cat.c
 * Ubuntu da hazır bulunan cat'in yeniden yapılması
 */


#include <stdio.h>
#include <string.h>
/*Çağırıan dosyayı veya dosyaları okur ekrana yazdıran fonksiyondur
 *Eğer main -n opsiyonu ile çağırılırsa Tüm satırları numaralandırıp öyle yazdırır
 *Eğer main -b opsiyonu ile çağırılırsa Boş Olmayan satırları numaralandırıp öyle yazdırır*/
int FileRead(int argc, char **argv){
	FILE *f;
	int j=1;
	if(strcmp(argv[1],"-n")==0){ /*Eğer -n opsiyonu çağırıldıysa satırları numaralandırıp output eder*/
		for(int i = 2 ; i <= argc ; i++){
			f = fopen(argv[i],"r");
			if(f == NULL){
				return 0;
			}
			char s[250];
			while(fgets(s,250,f) != NULL){  /*Satır sonuna gelene kadar diziye okur ve satırları numaralandırıp yazdırır*/
				printf("%d- %.250s",j,s);
				j++;
			}
			printf("\n");
		}
		fclose(f);
	}
	else if(strcmp(argv[1],"-b")==0){ /*Eğer -b opsiyonu çağırıldıysa boş olmayan satırları numaralandırıp output eder*/
		for(int i = 2 ; i <= argc ; i++){
			f = fopen(argv[i],"r");
			if(f == NULL){
				return 0;
			}
			char s[250];
			int i=1;
			while(fgets(s,250,f) != NULL){ /*Satırsonuna gelene kadar diziye okur ve boş olmayan satırları numaralandırıp yazdırır*/
				if(s[1] != '\0'){
					printf("%d- %.250s",i,s);
					i++;
				}
				else{
					printf("\n");
				}
			}
			printf("\n");
			
		}
		fclose(f);
	}
	else{ /*Hangi dosya veya ddosyalar ile çağırıldıysa onları output eder*/
		for(int i = 1 ; i <= argc ; i++){
			f = fopen(argv[i],"r");
			if(f == NULL){
				return 0;
			}
			char c;
			while((c = fgetc(f)) != EOF){ /*Dosyadan EOF olana kadar Karakter Karakter okur ve stdouta gönderip ekrana yazdırır*/
				fputc(c,stdout);
			}
			printf("\n");
		}
		fclose(f);
	}
	return 1;
}
/*Bir veya birden fazla dosyayı başka bir dosyaya kopyalayan fonksiyondur
 * Eğer ">" argümanı ile çağırılmışsa klavyeden girilenleri dosyaya okur
 * Eğer main -n opsiyonu ile çağırılmişsa tüm satırları numaralandırıp öyle dosyaya yazdırır(">" argümanı ile çağırma dahil)
 * Eğer main -b opsiyonu ile çağırılmişsa boş olmayan satırları numaralandırıp öyle yazdırır (">" argümanı ile çağırma dahil)
 */
int FileCopy(int argc, char **argv){
	FILE *f, *f2;
	int a = 1;
	int b = 4;
	int c = 3;
	int x = 1;
	int y = 2;
	int say = 1;
	if((strcmp(argv[a], "-n") == 0) || (strcmp(argv[a], "-b") == 0)){ /*Main -n veya -b opsiyonları ile çağırılmışsa */
		a = 2;														/*Fonksiyonun değişkenlerini ona göre değiştirir(Bir arttırır) */
		b = 5;
		c = 4;
		x = 2;
		y = 3;
	}
	while(1){
		if(strcmp(argv[a], ">") == 0){ /*">" argümanının yerini tespit eder*/
			break;
		}
		else{
		a++;	
		}
	}
	if((a == argc-2)&&(argc >= b)){ 		/*">" argümanı sonndan bir önceki argüman ise bu argümana kadar olan dosyaları son argümanın*/
		for(int i = 0; i <= argc; i++){		/*belirttiği dosyaya kopyalar*/
			if((i == a+1) || (i == 0) || (i == argc-1)){ /*">" argümanı , dosya ismini tutan pointer veya argv nin son elemanı ise devam et*/
			continue;									/*i değeri ile dosya okuması yaptığı için hatalı bir okuma yapmasın diye*/
			}
			else if(i == x){ /*Birden fazla dosyayı tek bir dosyaya kopyalayacaksa ilk dosyayı acarken kopyalanacak dosyayı sıfırlayıp açar*/
				f = fopen(argv[i],"r"); /*Daha sonraki dosyaları okurken sonuna ekleme modunda açar.İlk dosyayı Kopyalar*/
				if(f == NULL){
					return 0;
				}
				f2 = fopen(argv[a+1],"w");
				char c;
				if(strcmp(argv[1], "-n") == 0){ /*-n opsiyonu ile çağırılmışsa main açılan dosyanın ilk satırı numaralandır*/
					fprintf(f2,"%d- ", say);
					say++;
				}
				while((c = fgetc(f)) != EOF){
					putc(c, f2);
					if(strcmp(argv[1], "-n") == 0){ /*-n opsiyonu ile çağırılmışsa main diğer satırları numaralandır*/
						if(c == '\n'){
							fprintf(f2,"%d- ", say);
							say++;
						}
					}
				}
				fprintf(f2,"\n");
				fclose(f);
				fclose(f2);
			}
			else{ /*Kopyalanacak dosyayı ekleme modunda açar ve ilk dosyadan sonraki dosyları tek tek kopyalar*/
				f = fopen(argv[i],"r");
				if(f == NULL){
					return 0;
				}
				f2 = fopen(argv[a+1],"a");
				
				char c;
				if(strcmp(argv[1], "-n") == 0){ /*-n opsiyonu ile çağırılmışsa main açılan dosyanın ilk satırı numaralandır*/
					fprintf(f2,"%d- ", say);
					say++;
				}
				while((c = fgetc(f)) != EOF){
					fputc(c, f2);
					if(strcmp(argv[1], "-n") == 0){ /*-n opsiyonu ile çağırılmışsa main diğer satırları numaralandır*/
						if(c == '\n'){
							fprintf(f2,"%d- ", say);
							say++;
						}
					}
				}
				fclose(f);
				fclose(f2);
			}
		}
	}
	else if((argc == c)&&(strcmp(argv[a], ">") == 0)){ /*Eğer ">" argümanı ilk argümansa klavyeden girilen değişkenleri dosyaya kopyalar*/
		f = fopen(argv[y], "w");
		char a;
		int say2 = 1;
		if(strcmp(argv[1], "-n") == 0){ /*-n opsiyonu ile çağırılmışsa main ilk satırı numaralandır*/
			fprintf(f,"%d-", say2);
			say2++;
		}
		while((a = fgetc(stdin)) != EOF){
			fputc(a, f);
			if(strcmp(argv[1], "-n") == 0){ /*-n opsiyonu ile çağırılmışsa main diğer satırları numaralandır*/
				if(a == '\n'){
					fprintf(f,"%d-", say2);
					say2++;	
				}
			}
		}
		fclose(f);	
	}
	else{
		printf("\tHatali Giris!\n");
		printf("Lutfen Asagidakiler Gibi Giris Yapiniz:\n");
		printf("cat file1.txt \">\" file2.txt \n");
		printf("cat file1.txt file2.txt \">\" file3.txt\n");
		printf("cat \">\" file1.txt\n");
	}
	
	return 0;
}

int main(int argc, char **argv){
	int a = 0;
	int j = 0;
		while(argv[a] != NULL){ /*Cagırılan argumanlar arasında ">" argumanı var mı kontrol eder*/
			if(strncmp(argv[a], ">",15) == 0){
				j++;
			}
			a++;	
		}
	if((j == 0) && (strcmp(argv[1], "-h") != 0)){ /*Eger hiç ">" argumanı ile cagırlmamıssa okuma yapan fonksiyonu cagırır*/
		printf("Okunuyor...:\n");
		FileRead(argc,argv);
	}
	else if(j == 1){ /*Eger 1 tane ">" argumanı ile cagırılmıssa copyalama yapan fonksyonu cagırır*/
		printf("Kopyalanıyor...\n");
		printf("Kopyalandı\n");
		FileCopy(argc, argv);
	}
	else if((strcmp(argv[1], "-h") ==0) && argc ==2){ /*Eger main -h argumanı ile cagırılmıssa Cat in işlevlerini ve kullanınımını anlatan bilgiler yazdırır*/
		printf("\nCat fonksiyonu temelde 3 tane");
		printf("işlev sunan komutlardan biridir. Bu islevler:");
		printf("bir metin dosyasi iceriginin goruntulenmesi, kopyalarin birlestirilmesi ");
		printf("(farkli metin dosyasi iceriklerinin vb.) ve kopyalardan (farkli metin dosyasi iceriklerinden)");
		printf("yeni bir metin icerigi olusturulmasi.");
		printf("\n\n \t\t\tKOMUTLAR");
		printf("\n\n -b komutu ==> Bos olmayan satirlari numaralandirir.");
		printf("\n -h komutu ==> Yazilan cat programin nasil kullanildigiyla ilgili kisa ornek ve acıklamalar gösterir.");
		printf("\n -n komutu ==> Tum satirlari numaralandirir.\n");
		printf("\n \t\tORNEK KOMUT KULLANIMLARI");
		printf("\n\ncat file1.txt \">\" file2.txt");
		printf("\ncat file1.txt file2.txt \">\" file3.txt");
		printf("\ncat \">\" file1.txt");
		
	}
	else
	return 0;
}

