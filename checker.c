#include <stdio.h>
#include <assert.h>

int test_scan(char test_case[], char sentence[]) {
	int quoteIndex = -1;
	char ooga = "";

	printf("%-50s: ================================================================\n", test_case);
	printf("ml' nob:%s", sentence);
    int conversions = sscanf(sentence, "%d%c", &quoteIndex, &ooga);
    printf("\t%d argument(s)", conversions);
    if (conversions > 0) {
        printf(". #1 %d", quoteIndex);
    }
    if (conversions > 1) {
        printf(". #2 0x%x", ooga);
    }    
    printf("\n");

	if (conversions != 2) {
		printf("Neh mi'\n");
		return 1;
	}
	if (ooga != '\n') {
		printf("bIjatlh 'e' yImev\n");
		return 1;
	}
	if (quoteIndex < 0 || quoteIndex > 8) {
		printf("Qih mi' %d\n", quoteIndex);
		return 1;
	}


	printf("Qapla'\n");

	switch (quoteIndex) {
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

void test_test_scan_valid_input() {
    char sentence[] = "5\n";
    int result = test_scan("Unit test: valid_input", sentence);
    assert(result == 0);
}

void test_test_scan_invalid_quoteIndex() {
    char sentence[] = "-1\n";
    int result = test_scan("Unit test: invalid_quoteIndex", sentence);
    assert(result == 1);
}

void test_test_scan_invalid_ooga() {
    char sentence[] = "5a";
    int result = test_scan("Unit test: invalid_ooga", sentence);
    assert(result == 1);
}

void test_test_scan_missing_arguments() {
    char sentence[] = "5";
    int result = test_scan("Unit test: missing_arguments", sentence);
    assert(result == 1);
}

void test_test_scan_extra_arguments() {
    char sentence[] = "5a2";
    int result = test_scan("Unit test: extra_arguments", sentence);
    assert(result == 1);
}

int unit_tests() {
    test_test_scan_valid_input();
    test_test_scan_invalid_quoteIndex();
    test_test_scan_invalid_ooga();
    test_test_scan_missing_arguments();
    test_test_scan_extra_arguments();
    printf("All tests passed!\n");
    return 0;
}

int main() {
    test_scan("0", "0\n");
    test_scan("1", "1\n");
    test_scan("2", "2\n");
    test_scan("3", "3\n");
    test_scan("4", "4\n");
    test_scan("5", "5\n");
    test_scan("6", "6\n");
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

    unit_tests();
}    