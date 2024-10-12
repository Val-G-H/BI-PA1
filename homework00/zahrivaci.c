#include <stdio.h>
#include <math.h>

#define MAX_LIMIT 5000

int main() {
	
	float quoteNumber_f;
    char str[MAX_LIMIT] = {0};
    
    float intpart_f, fracpart_f;
    int intpart_i;

    printf("ml' nob:\n");
    int conversions = scanf("%f %5000c", &quoteNumber_f, str);
    // conversions can be -1 (EOF), 0 or up to the # of scanf variables, e.g. 3
    
    // there is no number
    if ((conversions == 0) || (conversions == EOF)) {
        printf("Neh mi'\n");
        return 1;
    }

    // extract the integer part
    fracpart_f = modff(quoteNumber_f, &intpart_f);
    intpart_i = intpart_f;
    
    // the number comes with a fractional part too
    if (fracpart_f != 0) {
        printf("bIjatlh 'e' yImev\n");
        return 1;
    }

    // the number is followed by something more
    if (conversions == 2) {
        printf("bIjatlh 'e' yImev\n");
        return 1;
    }
    
    // the number is outside of quotation range
	if ((intpart_i < 0) || (intpart_i > 8)) {
		printf("Qih mi' %d\n", intpart_i);
		return 1;
	}
    
	printf("Qapla'\n");
	switch (intpart_i) {
		case 0:
			printf("noH QapmeH wo' Qaw'lu'chugh yay chavbe'lu' 'ej wo' choqmeH may' DoHlu'chugh lujbe'lu'.\n");
			break;
		case 1:
			printf("bortaS bIr jablu'DI' reH QaQqu' nay'.\n");
			break;
		case 2:
			printf("Qu' buSHa'chugh SuvwI', batlhHa' vangchugh, qoj matlhHa'chugh, pagh ghaH SuvwI''e'.\n");
			break;
		case 3:
			printf("bISeH'eghlaH'be'chugh latlh Dara'laH'be'.\n");
			break;
		case 4:
			printf("qaStaHvIS wa' ram loS SaD Hugh SIjlaH qetbogh loD.\n");
			break;
		case 5:
			printf("Suvlu'taHvIS yapbe' HoS neH.\n");
			break;
		case 6:
			printf("Ha'DIbaH DaSop 'e' DaHechbe'chugh yIHoHQo'.\n");
			break;
		case 7:
			printf("Heghlu'meH QaQ jajvam.\n");
			break;
		case 8:
			printf("leghlaHchu'be'chugh mIn lo'laHbe' taj jej.\n");
			break;
	}
    return 0;
}    
