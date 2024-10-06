#include <stdio.h>
#include <math.h>

#define MAX_LIMIT 5000

void print_dumper(const char *test_case, int conversions, float quoteNumber_f, char *str, char ooga) {
    printf("\t\t%s: ================================================================\n", test_case);
    printf("\t\t%s: %d argument(s)", test_case, conversions);
    if (conversions > 0) {
        printf(". #1 %f", quoteNumber_f);
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
    if (conversions > 2) {
        printf(". #3 ASCII: %d", ooga);
    }
    printf("\n");
}

int test_scan(char *test_case, char *sentence) {
    float quoteNumber_f;
    char str[MAX_LIMIT];
    char ooga = '\0';
    
    float intpart_f, fracpart_f;
    int intpart_i;

    printf("ml' nob:%s", sentence);
    int conversions = sscanf(sentence, "%f%5000[^0123456789]%c", &quoteNumber_f, str, &ooga);
    // conversions can be -1 (EOF), 0 or up to the # of scanf variables, e.g. 3
    
    // there is no number
    if ((conversions == 0) || (conversions == EOF)) {
        printf("Neh mi'\n");
        // print_dumper(test_case, conversions, quoteNumber_f, str, ooga);
        return 1;
    }

    // extract the integer part
    fracpart_f = modff(quoteNumber_f, &intpart_f);
    intpart_i = intpart_f;
    
    // the number comes with a fractional part too
    if (fracpart_f != 0) {
        printf("bIjatlh 'e' yImev\n");
        // print_dumper(test_case, conversions, quoteNumber_f, str, ooga);
        return 1;
    }
    
    // the number is outside of quotation range
	if ((intpart_i < 0) || (intpart_i > 8)) {
		printf("Qih mi' %d\n", intpart_i);
        // print_dumper(test_case, conversions, quoteNumber_f, str, ooga);
		return 1;
	}

    // the number is followed by something, and it is not a Linux new line delimeter (0x0a)
    if (((conversions == 2) && (str[0] != 0x0a)) || (conversions == 3)) {
        printf("bIjatlh 'e' yImev\n");
        print_dumper(test_case, conversions, quoteNumber_f, str, ooga);
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
    
    test_scan("Extra #0", "-1.23\n");
    test_scan("Extra #1", "1.a\n");
    test_scan("Extra #2", "a1\n");
    test_scan("Extra #3", "1.23a\n");
    test_scan("Extra #4", "1.23ab\n");
    test_scan("Extra #5", "1.23a4.56\n");

    test_scan("Extra #6", "1abcd\n");
    test_scan("Extra #7", "-1abcd\n");
    test_scan("Extra #8", "01abcd\n");
    test_scan("Extra #9", "1abcd1\n");
    test_scan("Extra #10", "1abcd1a\n");
}    