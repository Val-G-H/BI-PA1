# Introduction

Assignment:
- prečist tři body A, B, C
- spočitat tři nove body tak aby tvořili rovnoběžniky ABA'C, ABCB' a AC'BC
- určit připadny specialní tvar obrazce
- vstup je neplatný pokud
    - nečíselné zadání souřadnic (neplatné desetinné číslo),
    - chybějící souřadnice,
    -c hybějící nebo přebývající oddělovače (souřadnice musí být zadaná v hranatých závorkách, hodnoty x a y musí být oddělené čárkou).

Refer to the [assignment details here](Assignment.txt)

# Current solution

1. Прочитать координаты точки А в формате `[x, y]`. Числа принимаются в формате `double`, между символами могут быть пустые знаки, ввод обязательно заканчивается символом `]`
    - несоотсветствие формату - ошибка `Nespravny vystup.`

2. Прочитать координаты точки B в формате `[x, y]`
    - несоотсветствие формату - ошибка `Nespravny vystup.`

3. Прочитать координаты точки C в формате `[x, y]`
    - несоотсветствие формату - ошибка `Nespravny vystup.`

4. Проверка: лежат ли три точки на одной прямой? Если они лежат на одной прямой, площадь треугольника, который они образуют равна 0
    - невозможно создать параллелограмм - ошибка `Rovnobezniky nelze sestrojit.`

5. Подсчет координат новых точек A', B', C' (`newA`, `newB`, `newC`). Для этого вектор из одной точки во вторую выпускаем из третьей. 
Пример: новая фигура `ABA'C`, координаты точки `A'` получаем если вектор `AB` выпустить из точки `C`, или вектор `AC` из точки `B`
```
A'[x, y] = C[x, y] + AB[x, y]
AB[x, y] = B[x, y] - A[x, y]
A'[x, y] = C[x, y] + B[x, y] - A[x, y]
```

6. Посчитать [скалярное произведение](https://en.wikipedia.org/wiki/Dot_product) двух векторов из каждого угла треугольника `ABC`.

7. Проверка: сравнить скалярное произведение с нулем. Если они равны, то этот угол прямой и соответственно в этой фигуре все углы прямые.

8. Посчитать скалярную длину сторон `AB`, `AC`, `A'B`, `AB'`, `AC'`
Пример:
```
|AB| = SQRT( (B[x] - A[x])^2 + (B[y] - A[y])^2 )
```

8. Проверка: сравнить две касающиеся стороны из каждой новой фигуры. Если они равны, то во всей фигуре равные стороны.

Дополнительные материалы о сравнении double:
- [IEEE Standard 754 Floating Point Numbers](https://steve.hollasch.net/cgindex/coding/ieeefloat.html)
- [Comparing floating point numbers](https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/)

10. Выписать координаты каждой из новых точек в формате Z': [x, y] и определить тип фигуры, созданный этой новой точкой.
    - Если все углы прямые и все стороны равны - квадрат `ctverec`
    - Если все стороны равны - ромб `kosoctverec`
    - Если все углы прямные - прямоугольник `obdelnik`
    - Если ни одно из предыдущих условий не выполняется - параллелограмм `rovnobeznik` 




Refer to [implementation here](hw01_hard.c)

# Tests

Local tests via terminal script

`for file in CZE/*_in.txt; do echo "$file"; ./a.out < "$file" | diff - "${file/in/out}"; done`
