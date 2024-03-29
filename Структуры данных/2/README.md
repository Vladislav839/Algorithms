# Задача 27.1. Межшкольная сеть

Имя входного файла: input.txt

Имя выходного файла: output.txt

Ограничение по времени: 1 с

Ограничение по памяти: нет

Некоторые школы связаны компьютерной сетью. Между школами заключены соглашения: каждая школа имеет список школ-получателей, которым она рассылает программное обеспечение всякий раз, получив новое бесплатное программное обеспечение (извне сети или из другой школы). При этом если школа $b$ есть в списке получателей школы $a$, то школа $a$ может и не быть в списке получателей школы $b$.

Необходимо решить следующие две подзадачи.

Определить минимальное число школ, которым надо передать по экземпляру нового программного обеспечения, чтобы распространить его по всем школам сети в соответствии с соглашениями.
Обеспечить возможность рассылки нового программного обеспечения из любой школы по всем остальным школам. Для этого можно расширять списки получателей некоторых школ, добавляя в них новые школы. Требуется найти минимальное суммарное число расширений списков, при которых программное обеспечение из любой школы достигло бы всех остальных школ. Под расширением понимается добавление одной новой школы-получателя в список получателей одной из школ.
# Формат входных данных
Первая строка содержит число $n$ школ в сети $(2 ≤ n ≤ 100)$. Школы нумеруются первыми $n$ положительными целыми числами.
Каждая из следующих $n$ строк задаёт список получателей. Строка $i + 1$ содержит номера получателей $i$-й школы. Каждый такой список заканчивается нулём. Пустой список содержит только ноль.

# Формат выходных данных
В первой строке выведите решение первой подзадачи.
Во второй строке — минимальное суммарное число $k$ расширений списков.

# Пример

![title](https://drive.google.com/uc?export=view&id=1lIaHtTAYfHT3mc9eZc0pL1VT5EVVuqbU)