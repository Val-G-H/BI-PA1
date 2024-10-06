# Introduction

Assignment:
- ze vstupu nelze přečíst celé číslo
- číslo přečtené ze vstupu je mimo interval 0 až 8
- Vstup typu 1.23 případně 1abcd není správný

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

# Alternative solution (UNDER DESIGN)

- Мы получили первую группу (с числом)?
	- Нет - ОШИБКА1 [Neh mi']
	- Да - Это число нецелое?
		- Да - ОШИБКА3 [bIjatlh 'e' yImev] // OI: А может надо и ОШИБКА1 [Neh mi'] если после числа что-то есть?
		- Нет - Мы получили вторую группу и там не только перенос строкимы получили и третью группу? // OI: Возможно на третью группу надо ОШИБКА1 [Neh mi']?
				- Да - ОШИБКА3 [bIjatlh 'e' yImev]
				- Нет - Число в диапазоне от 0 до 8?				
					- Нет - ОШИБКА2 [Qih mi' %D]
					- Да - показать цитату

Current output for the OIs:
```
ml' nob:1.23a
bIjatlh 'e' yImev
ml' nob:1.23ab
bIjatlh 'e' yImev
ml' nob:1.23a4.56
bIjatlh 'e' yImev
ml' nob:1abcd
bIjatlh 'e' yImev
ml' nob:-1abcd
bIjatlh 'e' yImev
ml' nob:01abcd
bIjatlh 'e' yImev
ml' nob:1abcd1
bIjatlh 'e' yImev
ml' nob:1abcd1a
bIjatlh 'e' yImev
```

# How to run

Use [online compiler](https://rextester.com/l/c_online_compiler_gcc)

For the _gcc parameters_ set:
'-Wall -pedantic'

# Reference materials

For the C libraries, refer to [c++.com](https://cplusplus.com/reference/clibrary/)