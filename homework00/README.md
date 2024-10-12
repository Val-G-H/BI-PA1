# Introduction

Assignment:
- ze vstupu nelze přečíst celé číslo
- číslo přečtené ze vstupu je mimo interval 0 až 8
- Vstup typu 1.23 případně 1abcd není správný

Refer to the [assignment details here](Assignment.txt)

# Current solution

1. Попробовать получить целое число, а потом один символ
2. Запомнить сколько получили
 
3. Получили не два?
	- ОШИБКА1 [Neh mi']

4. _следующий после числа_ символ не перенос строки?
	- ОШИБКА3 [bIjatlh 'e' yImev]

5. Целое число вне диапазона?
	- ОШИБКА2 [Qih mi' %D]

6. Показать цитату

Refer to [implementation here](zahrivaci.c)

# Alternative solution (UNDER DESIGN)

- Мы получили первую группу (с числом)?
	- Нет - ОШИБКА1 [Neh mi']
	- Да - Это число нецелое?
		- Да - ОШИБКА3 [bIjatlh 'e' yImev]
		- Нет - Мы получили вторую группу?
			- Да - ОШИБКА3 [bIjatlh 'e' yImev]
			- Нет - Число в диапазоне от 0 до 8?				
				- Нет - ОШИБКА2 [Qih mi' %D]
				- Да - показать цитату

Refer to [implementation here](checker.c)

Current output:
```
ml' nob:0
Qapla'
noH QapmeH wo' Qaw'lu'chugh yay chavbe'lu' 'ej wo' choqmeH may' DoHlu'chugh lujbe'lu'.
		0: ================================================================
		0: 1 argument(s). #1 0.000000
ml' nob:1
Qapla'
bortaS bIr jablu'DI' reH QaQqu' nay'.
		1: ================================================================
		1: 1 argument(s). #1 1.000000
ml' nob:007
Qapla'
Heghlu'meH QaQ jajvam.
		7: ================================================================
		7: 1 argument(s). #1 7.000000
ml' nob:           8
Qapla'
leghlaHchu'be'chugh mIn lo'laHbe' taj jej.
		8: ================================================================
		8: 1 argument(s). #1 8.000000
ml' nob:29
Qih mi' 29
		9: ================================================================
		9: 1 argument(s). #1 29.000000
ml' nob:-5
Qih mi' -5
		10: ================================================================
		10: 1 argument(s). #1 -5.000000
ml' nob:abc
Neh mi'
		11: ================================================================
		11: 0 argument(s)
ml' nob:1.23
bIjatlh 'e' yImev
		12: ================================================================
		12: 1 argument(s). #1 1.230000
ml' nob:1abcd
bIjatlh 'e' yImev
		13: ================================================================
		13: 2 argument(s). #1 1.000000. #2 'abcd
'
ml' nob:8J
bIjatlh 'e' yImev
		14: ================================================================
		14: 2 argument(s). #1 8.000000. #2 'J
'
ml' nob:1NZKXTDTSUPFZFYOWRQDFORKUPXYANRSHCWRFTASUTHNMMCSAMOWCMOKBOFGJDABPVCLGFCCXLJKZMMYMTKQFEBYHHFXMPFQIQIYNFHLARXEHWDHMJQRRBRITEOVPYUBMISJXGKJLSFQQTFPOMSWTWQZQPMGCNKQXOXPPYJKWXCHIBVNZCQKTAVAOPMOKWHNQJPLERBHKUZENABZXYGOCJKZMSPJMDITRTPHODOAFPMGUJMZCVGMKOHEMDTZEUISUDEHOEEXVOTEGKINDPJMUSGJCKUFFMFEIUJWTRXYRMKZVWKGKPIJJNKERUUIJAXCNYFNCYNIEWCWVTQHJEXQVBRTCOSLUALYACYJJAGKKSLWCRLKBJMNHTVCODKDTHASXWNYOKVMAOIYMQTOFOFLEYWSWPCNTQQHVDQGKUJOVKUSNSOZCPLGKZNAKOEGTIFXARIQMGUGWYMLOPHFZUFJOMETCGJJPGBSSYWPJJLHUDBCQEZAVDGAJPHOUTKVDGWHBSMSTWVVQSXKTNXJFSZXIZRIMSUADQEQIPKALYNHSYNYSABSGDYVLCPSLGHWXTCXIKIWDRUJWWRIOJITMIKOZYXLTYNTVKRJMNNILMTDJFEJKBFRCIGZULMVSMDPNVPSUWKSJBBTMWZLBDKOEADEIADEAEGDZFMARKQYAIHXSNLSSMAFWPTBFUSBOYEPGSEIQQQTELSXUGSNVAKIXKUSOJPUCSWSEIEXUWUBSRVUTNAVXWUFDTIGYOKTLPHWTYWYHTVDWMEXSJMSFYOMAZMUZKESOBNSFKQEIBDNRSEHCRTTXCFQIOMPSPQGEOCACSBPNFFFZOZVFIVUSFYLDPNDMMDBKFTZAJYOMTVOORIFLOCJAVEELAMVJPMDYBNGZQJNYOLADUTLWGMOTJLVIMIOVELISEEHZXNLXISDIFLHIZQPPYFCCWGMFYGJWOEYWMVWPOQZIWPJATISSNGEHKPZQLWHVUYZMULIIOACVFLZKYXTGLULCJRXZRXUOJKVZMKU
bIjatlh 'e' yImev
		15: ================================================================
		15: 2 argument(s). #1 1.000000. #2 'NZKXTDTSUPFZFYOWRQDFORKUPXYANRSHCWRFTASUTHNMMCSAMOWCMOKBOFGJDABPVCLGFCCXLJKZMMYMTKQFEBYHHFXMPFQIQIYNFHLARXEHWDHMJQRRBRITEOVPYUBMISJXGKJLSFQQTFPOMSWTWQZQPMGCNKQXOXPPYJKWXCHIBVNZCQKTAVAOPMOKWHNQJPLERBHKUZENABZXYGOCJKZMSPJMDITRTPHODOAFPMGUJMZCVGMKOHEMDTZEUISUDEHOEEXVOTEGKINDPJMUSGJCKUFFMFEIUJWTRXYRMKZVWKGKPIJJNKERUUIJAXCNYFNCYNIEWCWVTQHJEXQVBRTCOSLUALYACYJJAGKKSLWCRLKBJMNHTVCODKDTHASXWNYOKVMAOIYMQTOFOFLEYWSWPCNTQQHVDQGKUJOVKUSNSOZCPLGKZNAKOEGTIFXARIQMGUGWYMLOPHFZUFJOMETCGJJPGBSSYWPJJLHUDBCQEZAVDGAJPHOUTKVDGWHBSMSTWVVQSXKTNXJFSZXIZRIMSUADQEQIPKALYNHSYNYSABSGDYVLCPSLGHWXTCXIKIWDRUJWWRIOJITMIKOZYXLTYNTVKRJMNNILMTDJFEJKBFRCIGZULMVSMDPNVPSUWKSJBBTMWZLBDKOEADEIADEAEGDZFMARKQYAIHXSNLSSMAFWPTBFUSBOYEPGSEIQQQTELSXUGSNVAKIXKUSOJPUCSWSEIEXUWUBSRVUTNAVXWUFDTIGYOKTLPHWTYWYHTVDWMEXSJMSFYOMAZMUZKESOBNSFKQEIBDNRSEHCRTTXCFQIOMPSPQGEOCACSBPNFFFZOZVFIVUSFYLDPNDMMDBKFTZAJYOMTVOORIFLOCJAVEELAMVJPMDYBNGZQJNYOLADUTLWGMOTJLVIMIOVELISEEHZXNLXISDIFLHIZQPPYFCCWGMFYGJWOEYWMVWPOQZIWPJATISSNGEHKPZQLWHVUYZMULIIOACVFLZKYXTGLULCJRXZRXUOJKVZMKU
'
ml' nob:-1.23
bIjatlh 'e' yImev
		Extra #0: ================================================================
		Extra #0: 1 argument(s). #1 -1.230000
ml' nob:1.a
bIjatlh 'e' yImev
		Extra #1: ================================================================
		Extra #1: 2 argument(s). #1 1.000000. #2 'a
'
ml' nob:a1
Neh mi'
		Extra #2: ================================================================
		Extra #2: 0 argument(s)
ml' nob:1.23a
bIjatlh 'e' yImev
		Extra #3: ================================================================
		Extra #3: 2 argument(s). #1 1.230000. #2 'a
'
ml' nob:1.23ab
bIjatlh 'e' yImev
		Extra #4: ================================================================
		Extra #4: 2 argument(s). #1 1.230000. #2 'ab
'
ml' nob:1.23a4.56
bIjatlh 'e' yImev
		Extra #5: ================================================================
		Extra #5: 2 argument(s). #1 1.230000. #2 'a4.56
'
ml' nob:1abcd
bIjatlh 'e' yImev
		Extra #6: ================================================================
		Extra #6: 2 argument(s). #1 1.000000. #2 'abcd
'
ml' nob:-1abcd
bIjatlh 'e' yImev
		Extra #7: ================================================================
		Extra #7: 2 argument(s). #1 -1.000000. #2 'abcd
'
ml' nob:01abcd
bIjatlh 'e' yImev
		Extra #8: ================================================================
		Extra #8: 2 argument(s). #1 1.000000. #2 'abcd
'
ml' nob:1abcd1
bIjatlh 'e' yImev
		Extra #9: ================================================================
		Extra #9: 2 argument(s). #1 1.000000. #2 'abcd1
'
ml' nob:1abcd1a
bIjatlh 'e' yImev
		Extra #10: ================================================================
		Extra #10: 2 argument(s). #1 1.000000. #2 'abcd1a
'
ml' nob:1
2
bIjatlh 'e' yImev
		Added Example #1: ================================================================
		Added Example #1: 2 argument(s). #1 1.000000. #2 '2
'
ml' nob:1 
Qapla'
bortaS bIr jablu'DI' reH QaQqu' nay'.
		Added Example #2: ================================================================
		Added Example #2: 1 argument(s). #1 1.000000
ml' nob:1 Qapla'
bortaS bIr jablu'DI' reH QaQqu' nay'.
		Added Example #3: ================================================================
		Added Example #3: 1 argument(s). #1 1.000000
ml' nob:1 2
bIjatlh 'e' yImev
		Added Example #4: ================================================================
		Added Example #4: 2 argument(s). #1 1.000000. #2 '2
'
```