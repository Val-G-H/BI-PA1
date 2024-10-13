#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>

#define MAX_LIMIT 5000

void print_dumper(const char *test_case, int conversions, long long int quoteNumber, char *str) {
    printf("\t\t\tCase %s: ================================================================\n", test_case);
    printf("\t\t\tCase %s: Scanned %d argument(s)", test_case, conversions);
    if (conversions > 0) {
        printf(". #1 %lld", quoteNumber);
    }
    if (conversions > 1) {
        printf(". #2 '%s'", str);
        /*
        // Print the content of str with ASCII values
        printf("Content of str with ASCII values:\n");
        for (int i = 0; str[i] != '\0'; i++) {
            printf("Character #%d: '%c', ASCII: %d\n", i, str[i], str[i]);
        }
        */
    }
    printf("\n\t\t\tCase %s: ================================================================\n", test_case);
}

int test_scan(char *test_case, char *sentence) {
    long long int quoteNumber;
    char str[MAX_LIMIT] = {0};
    
    printf("Input: [%s]\nOutput:\n", sentence);

    char format[100];
    sprintf(format, "%%lld%%%ds", MAX_LIMIT - 1); // to leave space for the null terminator in the str array
    int conversions = sscanf(sentence, format, &quoteNumber, str);
    // conversions can be -1 (EOF), 0 or up to the # of scanf variables, e.g. 3

    // there is no number
    if ((conversions == 0) || (conversions == EOF)) {
        printf("Neh mi'\n");
        print_dumper(test_case, conversions, quoteNumber, str);
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
                print_dumper(test_case, conversions, quoteNumber, str);
                return 1;
            }
        }
    }

    // the number exceeds the limit
    if ((quoteNumber == LLONG_MIN) || (quoteNumber == LLONG_MAX)) {
        printf("bIjatlh 'e' yImev\n");
        print_dumper(test_case, conversions, quoteNumber, str);
        return 1;
    }

    // the number is outside of quotation range
	if ((quoteNumber < 0) || (quoteNumber > 8)) {
		printf("Qih mi' %lld\n", quoteNumber);
        print_dumper(test_case, conversions, quoteNumber, str);
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
    print_dumper(test_case, conversions, quoteNumber, str);    
    return 0;
}

int main() {
    test_scan("0", "0\n");
    test_scan("1", "1\n");
    test_scan("7", "007\n");
    test_scan("8", "           8\n");
    test_scan("9", "29\n");
    test_scan("10", "-5\n");
    test_scan("11", "abc\n");
    test_scan("12", "1.23\n");
    test_scan("13", "1abcd\n");
    test_scan("14", "8J\n");
    test_scan("15", "1NZKXTDTSUPFZFYOWRQDFORKUPXYANRSHCWRFTASUTHNMMCSAMOWCMOKBOFGJDABPVCLGFCCXLJKZMMYMTKQFEBYHHFXMPFQIQIYNFHLARXEHWDHMJQRRBRITEOVPYUBMISJXGKJLSFQQTFPOMSWTWQZQPMGCNKQXOXPPYJKWXCHIBVNZCQKTAVAOPMOKWHNQJPLERBHKUZENABZXYGOCJKZMSPJMDITRTPHODOAFPMGUJMZCVGMKOHEMDTZEUISUDEHOEEXVOTEGKINDPJMUSGJCKUFFMFEIUJWTRXYRMKZVWKGKPIJJNKERUUIJAXCNYFNCYNIEWCWVTQHJEXQVBRTCOSLUALYACYJJAGKKSLWCRLKBJMNHTVCODKDTHASXWNYOKVMAOIYMQTOFOFLEYWSWPCNTQQHVDQGKUJOVKUSNSOZCPLGKZNAKOEGTIFXARIQMGUGWYMLOPHFZUFJOMETCGJJPGBSSYWPJJLHUDBCQEZAVDGAJPHOUTKVDGWHBSMSTWVVQSXKTNXJFSZXIZRIMSUADQEQIPKALYNHSYNYSABSGDYVLCPSLGHWXTCXIKIWDRUJWWRIOJITMIKOZYXLTYNTVKRJMNNILMTDJFEJKBFRCIGZULMVSMDPNVPSUWKSJBBTMWZLBDKOEADEIADEAEGDZFMARKQYAIHXSNLSSMAFWPTBFUSBOYEPGSEIQQQTELSXUGSNVAKIXKUSOJPUCSWSEIEXUWUBSRVUTNAVXWUFDTIGYOKTLPHWTYWYHTVDWMEXSJMSFYOMAZMUZKESOBNSFKQEIBDNRSEHCRTTXCFQIOMPSPQGEOCACSBPNFFFZOZVFIVUSFYLDPNDMMDBKFTZAJYOMTVOORIFLOCJAVEELAMVJPMDYBNGZQJNYOLADUTLWGMOTJLVIMIOVELISEEHZXNLXISDIFLHIZQPPYFCCWGMFYGJWOEYWMVWPOQZIWPJATISSNGEHKPZQLWHVUYZMULIIOACVFLZKYXTGLULCJRXZRXUOJKVZMKU\n");
    
    test_scan("Bonus #1.1", "-1.23\n");
    test_scan("Bonus #1.2", "1.a\n");
    test_scan("Bonus #1.3", "a1\n");
    test_scan("Bonus #1.4", "1.23a\n");
    test_scan("Bonus #1.5", "1.23ab\n");
    test_scan("Bonus #1.6", "1.23a4.56\n");

    test_scan("Bonus #2.1", "-1abcd\n");
    test_scan("Bonus #2.2", "01abcd\n");
    test_scan("Bonus #2.2", "1abcd1\n");
    test_scan("Bonus #2.3", "1abcd1a\n");
    
    test_scan("Clarified #3.1", "1\n2\n");
    test_scan("Clarified #3.2", "1 \n");
    test_scan("Clarified #3.3", "1 ");
    test_scan("Clarified #3.4", "1 2\n");    

    test_scan("Extra #4.1", "\n\n\n1");
    test_scan("Extra #4.2", "\n1\n2\n");
    test_scan("Extra #4.3", "\n\n\n");
    test_scan("Extra #4.4", "99999999999999999999999999999999999999\n");
    test_scan("Extra #4.5", "99999999999999999999999999999999999999J\n");
    test_scan("Extra #4.7", "0.\n");
    test_scan("Extra #4.8", "0.1\n");
    test_scan("Extra #4.9", "0,1\n");
    test_scan("Extra #4.10", "0xa\n");
    test_scan("Extra #4.11", ".\n");
    test_scan("Extra #4.11", ". \n");
}