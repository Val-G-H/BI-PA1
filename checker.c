#include <stdio.h>
#include <math.h>

#define MAX_LIMIT 5000

int test_scan(char *test_case, char *sentence) {
	float quoteNumber;
    char str[MAX_LIMIT];
	char ooga[1];
    
    double intpart, fracpart;

	printf("%s: ================================================================\n", test_case);
	printf("ml' nob:%s", sentence);
    int conversions = sscanf(sentence, "%f%5000[^0123456789]%c", &quoteNumber, str, &ooga);
    printf("\t%d argument(s)", conversions);
    if (conversions > 0) {
        printf(". #1 %f", quoteNumber);
    }
    if (conversions > 1) {
        printf(". #2 %s", str);
    }    
    if (conversions > 2) {
        printf(". #3 0x%x", ooga);
    }    
    printf("\n");

    fracpart = modf(quoteNumber, &intpart);
    if (fracpart == 0) {
        printf("The %f number is an integer.\n", intpart);
    } else {
        printf("The %f number comes with a fractional part %f.\n", intpart, fracpart);
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