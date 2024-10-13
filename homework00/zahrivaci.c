#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>

#define MAX_LIMIT 5000

int main() {
	long long int quoteNumber;
    char str[MAX_LIMIT] = {0};

	printf("ml' nob:\n");

    char format[100];
    sprintf(format, "%%lld%%%ds", MAX_LIMIT - 1); // to leave space for the null terminator in the str array
    int conversions = scanf(format, &quoteNumber, str);
    // conversions can be -1 (EOF), 0 or up to the # of scanf variables, e.g. 3

    // there is no number
    if ((conversions == 0) || (conversions == EOF)) {
        printf("Neh mi'\n");
        return 1;
    }

    // the number is followed by something more
    if (conversions == 2) {
        char c;
        int i=0;
        while (str[i])
        {
            c=str[i];
            // is it only of whitespaces only?
            if (isspace(c)) {
                i++;
            } else {
                printf("bIjatlh 'e' yImev\n");
                return 1;
            }
        }
    }

    // the number exceeds the limit
    if ((quoteNumber == LLONG_MIN) || (quoteNumber == LLONG_MAX)) {
        printf("bIjatlh 'e' yImev\n");
        return 1;
    }

    // the number is outside of quotation range
	if ((quoteNumber < 0) || (quoteNumber > 8)) {
		printf("Qih mi' %lld\n", quoteNumber);
		return 1;
	}
    
	printf("Qapla'\n");
	switch (quoteNumber) {
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