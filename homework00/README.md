# Introduction

Assignment:
- ze vstupu nelze přečíst celé číslo
- číslo přečtené ze vstupu je mimo interval 0 až 8
- Vstup typu 1.23 případně 1abcd případně "1\n2\n" není správný

Refer to the [assignment details here](Assignment.txt)

# Solution

- Мы получили первую группу (с числом)?
	- Нет - ОШИБКА1 [Neh mi']

- Мы получили вторую (лишнюю) группу?
	- Да - В второй группе только white spaces?
		- Нет - ОШИБКА3 [bIjatlh 'e' yImev]

- Число на пределах long int?
	- Да - ОШИБКА3 [bIjatlh 'e' yImev]

- Число в диапазоне от 0 до 8?				
	- Нет - ОШИБКА2 [Qih mi' %D]

Показать цитату согласно числу

Refer to implemented [checker here](checker.c) and [final program here](zahrivaci.c)

# Tests

Checker's output:
```
Input: [0
]
Output:
Qapla'
noH QapmeH wo' Qaw'lu'chugh yay chavbe'lu' 'ej wo' choqmeH may' DoHlu'chugh lujbe'lu'.
			Case 0: ================================================================
			Case 0: Scanned 1 argument(s). #1 0
			Case 0: ================================================================
Input: [1
]
Output:
Qapla'
bortaS bIr jablu'DI' reH QaQqu' nay'.
			Case 1: ================================================================
			Case 1: Scanned 1 argument(s). #1 1
			Case 1: ================================================================
Input: [007
]
Output:
Qapla'
Heghlu'meH QaQ jajvam.
			Case 7: ================================================================
			Case 7: Scanned 1 argument(s). #1 7
			Case 7: ================================================================
Input: [           8
]
Output:
Qapla'
leghlaHchu'be'chugh mIn lo'laHbe' taj jej.
			Case 8: ================================================================
			Case 8: Scanned 1 argument(s). #1 8
			Case 8: ================================================================
Input: [29
]
Output:
Qih mi' 29
			Case 9: ================================================================
			Case 9: Scanned 1 argument(s). #1 29
			Case 9: ================================================================
Input: [-5
]
Output:
Qih mi' -5
			Case 10: ================================================================
			Case 10: Scanned 1 argument(s). #1 -5
			Case 10: ================================================================
Input: [abc
]
Output:
Neh mi'
			Case 11: ================================================================
			Case 11: Scanned 0 argument(s)
			Case 11: ================================================================
Input: [1.23
]
Output:
bIjatlh 'e' yImev
			Case 12: ================================================================
			Case 12: Scanned 2 argument(s). #1 1. #2 '.23'
			Case 12: ================================================================
Input: [1abcd
]
Output:
bIjatlh 'e' yImev
			Case 13: ================================================================
			Case 13: Scanned 2 argument(s). #1 1. #2 'abcd'
			Case 13: ================================================================
Input: [8J
]
Output:
bIjatlh 'e' yImev
			Case 14: ================================================================
			Case 14: Scanned 2 argument(s). #1 8. #2 'J'
			Case 14: ================================================================
Input: [1NZKXTDTSUPFZFYOWRQDFORKUPXYANRSHCWRFTASUTHNMMCSAMOWCMOKBOFGJDABPVCLGFCCXLJKZMMYMTKQFEBYHHFXMPFQIQIYNFHLARXEHWDHMJQRRBRITEOVPYUBMISJXGKJLSFQQTFPOMSWTWQZQPMGCNKQXOXPPYJKWXCHIBVNZCQKTAVAOPMOKWHNQJPLERBHKUZENABZXYGOCJKZMSPJMDITRTPHODOAFPMGUJMZCVGMKOHEMDTZEUISUDEHOEEXVOTEGKINDPJMUSGJCKUFFMFEIUJWTRXYRMKZVWKGKPIJJNKERUUIJAXCNYFNCYNIEWCWVTQHJEXQVBRTCOSLUALYACYJJAGKKSLWCRLKBJMNHTVCODKDTHASXWNYOKVMAOIYMQTOFOFLEYWSWPCNTQQHVDQGKUJOVKUSNSOZCPLGKZNAKOEGTIFXARIQMGUGWYMLOPHFZUFJOMETCGJJPGBSSYWPJJLHUDBCQEZAVDGAJPHOUTKVDGWHBSMSTWVVQSXKTNXJFSZXIZRIMSUADQEQIPKALYNHSYNYSABSGDYVLCPSLGHWXTCXIKIWDRUJWWRIOJITMIKOZYXLTYNTVKRJMNNILMTDJFEJKBFRCIGZULMVSMDPNVPSUWKSJBBTMWZLBDKOEADEIADEAEGDZFMARKQYAIHXSNLSSMAFWPTBFUSBOYEPGSEIQQQTELSXUGSNVAKIXKUSOJPUCSWSEIEXUWUBSRVUTNAVXWUFDTIGYOKTLPHWTYWYHTVDWMEXSJMSFYOMAZMUZKESOBNSFKQEIBDNRSEHCRTTXCFQIOMPSPQGEOCACSBPNFFFZOZVFIVUSFYLDPNDMMDBKFTZAJYOMTVOORIFLOCJAVEELAMVJPMDYBNGZQJNYOLADUTLWGMOTJLVIMIOVELISEEHZXNLXISDIFLHIZQPPYFCCWGMFYGJWOEYWMVWPOQZIWPJATISSNGEHKPZQLWHVUYZMULIIOACVFLZKYXTGLULCJRXZRXUOJKVZMKU
]
Output:
bIjatlh 'e' yImev
			Case 15: ================================================================
			Case 15: Scanned 2 argument(s). #1 1. #2 'NZKXTDTSUPFZFYOWRQDFORKUPXYANRSHCWRFTASUTHNMMCSAMOWCMOKBOFGJDABPVCLGFCCXLJKZMMYMTKQFEBYHHFXMPFQIQIYNFHLARXEHWDHMJQRRBRITEOVPYUBMISJXGKJLSFQQTFPOMSWTWQZQPMGCNKQXOXPPYJKWXCHIBVNZCQKTAVAOPMOKWHNQJPLERBHKUZENABZXYGOCJKZMSPJMDITRTPHODOAFPMGUJMZCVGMKOHEMDTZEUISUDEHOEEXVOTEGKINDPJMUSGJCKUFFMFEIUJWTRXYRMKZVWKGKPIJJNKERUUIJAXCNYFNCYNIEWCWVTQHJEXQVBRTCOSLUALYACYJJAGKKSLWCRLKBJMNHTVCODKDTHASXWNYOKVMAOIYMQTOFOFLEYWSWPCNTQQHVDQGKUJOVKUSNSOZCPLGKZNAKOEGTIFXARIQMGUGWYMLOPHFZUFJOMETCGJJPGBSSYWPJJLHUDBCQEZAVDGAJPHOUTKVDGWHBSMSTWVVQSXKTNXJFSZXIZRIMSUADQEQIPKALYNHSYNYSABSGDYVLCPSLGHWXTCXIKIWDRUJWWRIOJITMIKOZYXLTYNTVKRJMNNILMTDJFEJKBFRCIGZULMVSMDPNVPSUWKSJBBTMWZLBDKOEADEIADEAEGDZFMARKQYAIHXSNLSSMAFWPTBFUSBOYEPGSEIQQQTELSXUGSNVAKIXKUSOJPUCSWSEIEXUWUBSRVUTNAVXWUFDTIGYOKTLPHWTYWYHTVDWMEXSJMSFYOMAZMUZKESOBNSFKQEIBDNRSEHCRTTXCFQIOMPSPQGEOCACSBPNFFFZOZVFIVUSFYLDPNDMMDBKFTZAJYOMTVOORIFLOCJAVEELAMVJPMDYBNGZQJNYOLADUTLWGMOTJLVIMIOVELISEEHZXNLXISDIFLHIZQPPYFCCWGMFYGJWOEYWMVWPOQZIWPJATISSNGEHKPZQLWHVUYZMULIIOACVFLZKYXTGLULCJRXZRXUOJKVZMKU'
			Case 15: ================================================================
Input: [-1.23
]
Output:
bIjatlh 'e' yImev
			Case Bonus #1.1: ================================================================
			Case Bonus #1.1: Scanned 2 argument(s). #1 -1. #2 '.23'
			Case Bonus #1.1: ================================================================
Input: [1.a
]
Output:
bIjatlh 'e' yImev
			Case Bonus #1.2: ================================================================
			Case Bonus #1.2: Scanned 2 argument(s). #1 1. #2 '.a'
			Case Bonus #1.2: ================================================================
Input: [a1
]
Output:
Neh mi'
			Case Bonus #1.3: ================================================================
			Case Bonus #1.3: Scanned 0 argument(s)
			Case Bonus #1.3: ================================================================
Input: [1.23a
]
Output:
bIjatlh 'e' yImev
			Case Bonus #1.4: ================================================================
			Case Bonus #1.4: Scanned 2 argument(s). #1 1. #2 '.23a'
			Case Bonus #1.4: ================================================================
Input: [1.23ab
]
Output:
bIjatlh 'e' yImev
			Case Bonus #1.5: ================================================================
			Case Bonus #1.5: Scanned 2 argument(s). #1 1. #2 '.23ab'
			Case Bonus #1.5: ================================================================
Input: [1.23a4.56
]
Output:
bIjatlh 'e' yImev
			Case Bonus #1.6: ================================================================
			Case Bonus #1.6: Scanned 2 argument(s). #1 1. #2 '.23a4.56'
			Case Bonus #1.6: ================================================================
Input: [-1abcd
]
Output:
bIjatlh 'e' yImev
			Case Bonus #2.1: ================================================================
			Case Bonus #2.1: Scanned 2 argument(s). #1 -1. #2 'abcd'
			Case Bonus #2.1: ================================================================
Input: [01abcd
]
Output:
bIjatlh 'e' yImev
			Case Bonus #2.2: ================================================================
			Case Bonus #2.2: Scanned 2 argument(s). #1 1. #2 'abcd'
			Case Bonus #2.2: ================================================================
Input: [1abcd1
]
Output:
bIjatlh 'e' yImev
			Case Bonus #2.2: ================================================================
			Case Bonus #2.2: Scanned 2 argument(s). #1 1. #2 'abcd1'
			Case Bonus #2.2: ================================================================
Input: [1abcd1a
]
Output:
bIjatlh 'e' yImev
			Case Bonus #2.3: ================================================================
			Case Bonus #2.3: Scanned 2 argument(s). #1 1. #2 'abcd1a'
			Case Bonus #2.3: ================================================================
Input: [1
2
]
Output:
bIjatlh 'e' yImev
			Case Clarified #3.1: ================================================================
			Case Clarified #3.1: Scanned 2 argument(s). #1 1. #2 '2'
			Case Clarified #3.1: ================================================================
Input: [1 
]
Output:
Qapla'
bortaS bIr jablu'DI' reH QaQqu' nay'.
			Case Clarified #3.2: ================================================================
			Case Clarified #3.2: Scanned 1 argument(s). #1 1
			Case Clarified #3.2: ================================================================
Input: [1 ]
Output:
Qapla'
bortaS bIr jablu'DI' reH QaQqu' nay'.
			Case Clarified #3.3: ================================================================
			Case Clarified #3.3: Scanned 1 argument(s). #1 1
			Case Clarified #3.3: ================================================================
Input: [1 2
]
Output:
bIjatlh 'e' yImev
			Case Clarified #3.4: ================================================================
			Case Clarified #3.4: Scanned 2 argument(s). #1 1. #2 '2'
			Case Clarified #3.4: ================================================================
Input: [


1]
Output:
Qapla'
bortaS bIr jablu'DI' reH QaQqu' nay'.
			Case Extra #4.1: ================================================================
			Case Extra #4.1: Scanned 1 argument(s). #1 1
			Case Extra #4.1: ================================================================
Input: [
1
2
]
Output:
bIjatlh 'e' yImev
			Case Extra #4.2: ================================================================
			Case Extra #4.2: Scanned 2 argument(s). #1 1. #2 '2'
			Case Extra #4.2: ================================================================
Input: [


]
Output:
Neh mi'
			Case Extra #4.3: ================================================================
			Case Extra #4.3: Scanned -1 argument(s)
			Case Extra #4.3: ================================================================
Input: [99999999999999999999999999999999999999
]
Output:
bIjatlh 'e' yImev
			Case Extra #4.4: ================================================================
			Case Extra #4.4: Scanned 1 argument(s). #1 9223372036854775807
			Case Extra #4.4: ================================================================
Input: [99999999999999999999999999999999999999J
]
Output:
bIjatlh 'e' yImev
			Case Extra #4.5: ================================================================
			Case Extra #4.5: Scanned 2 argument(s). #1 9223372036854775807. #2 'J'
			Case Extra #4.5: ================================================================
Input: [0.
]
Output:
bIjatlh 'e' yImev
			Case Extra #4.7: ================================================================
			Case Extra #4.7: Scanned 2 argument(s). #1 0. #2 '.'
			Case Extra #4.7: ================================================================
Input: [0.1
]
Output:
bIjatlh 'e' yImev
			Case Extra #4.8: ================================================================
			Case Extra #4.8: Scanned 2 argument(s). #1 0. #2 '.1'
			Case Extra #4.8: ================================================================
Input: [0,1
]
Output:
bIjatlh 'e' yImev
			Case Extra #4.9: ================================================================
			Case Extra #4.9: Scanned 2 argument(s). #1 0. #2 ',1'
			Case Extra #4.9: ================================================================
Input: [0xa
]
Output:
bIjatlh 'e' yImev
			Case Extra #4.10: ================================================================
			Case Extra #4.10: Scanned 2 argument(s). #1 0. #2 'xa'
			Case Extra #4.10: ================================================================
Input: [.
]
Output:
Neh mi'
			Case Extra #4.11: ================================================================
			Case Extra #4.11: Scanned 0 argument(s)
			Case Extra #4.11: ================================================================
Input: [. 
]
Output:
Neh mi'
			Case Extra #4.11: ================================================================
			Case Extra #4.11: Scanned 0 argument(s)
			Case Extra #4.11: ================================================================
```