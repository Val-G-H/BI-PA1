ze vstupu nelze přečíst celé číslo
číslo přečtené ze vstupu je mimo interval 0 až 8
Vstup typu 1.23 případně 1abcd není správný

Основное:

Это просто число?
	Нет - ОШИБКА1 [Neh mi']
	Да - Оно в диапазоне?
		Нет - ОШИБКА2 [Qih mi' %D]
		Да - показать цитату

С бонусом:

Это просто число?
	Нет - Оно начинается с числа?
		Нет - ОШИБКА1 [Neh mi']
		Да - ОШИБКА3 [bIjatlh 'e' yImev]
	Да - Оно в диапазоне?
		Нет - ОШИБКА2 [Qih mi' %D]
		Да - показать цитату




Текущий алгоритм:

Попробовать получить целое число, а потом один символ
Запомнить сколько получили
 
Получили не два?
	Да - ОШИБКА1 [Neh mi']

_следующий после числа_ символ не перенос строки?
	Да - ОШИБКА3 [bIjatlh 'e' yImev]

Целое число вне диапазона?
	Да - ОШИБКА2 [Qih mi' %D]

Показать цитату

Новый алгоритм - с проверкой на нецелость числа:

Мы получили число?
	Нет - ОШИБКА1 [Neh mi']
	Да - Это число целое?
		Нет - ОШИБКА3 [bIjatlh 'e' yImev]
		Да - Оно в диапазоне от 0 до 8?
			Нет - ОШИБКА2 [Qih mi' %D]
			Да - показать цитату

Новый алгоритм - с проверкой на нецелость числа и текстом после числа:

Мы получили первую группу (с числом)?
	Нет - ОШИБКА1 [Neh mi']
	Да - Это число целое?
		Нет - ОШИБКА3 [bIjatlh 'e' yImev]
		Да - Оно в диапазоне от 0 до 8?
			Нет - ОШИБКА2 [Qih mi' %D]
			Да - Мы получили вторую группу и там только перенос строки?
				Нет - ОШИБКА3 [bIjatlh 'e' yImev]
				Да - показать цитату


Новый алгоритм - с проверкой на нецелость числа, текстом после числа и числами после текста после числа:

Мы получили первую группу (с числом)?
	Нет - ОШИБКА1 [Neh mi']
	Да - Это число целое?
		Нет - ОШИБКА3 [bIjatlh 'e' yImev] // bug: только после числа ничего нет. Если дальше что-то есть то ОШИБКА1 [Neh mi'] (extra #7 case)
		Да - Оно в диапазоне от 0 до 8?
			Нет - ОШИБКА2 [Qih mi' %D]
			Да - Мы получили вторую группу и там только перенос строки?
				Да - показать цитату
				Нет - Мы получили третью группу? // bug: сейчас всегда ОШИБКА3
					Нет - ОШИБКА3 [bIjatlh 'e' yImev]
					Да - ОШИБКА1 [Neh mi'] 


