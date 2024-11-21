//24. На вход подаются сведения о сдаче экзаменов учениками 9-х
//классов некоторой средней школы. В первой строке сообщается 
//количество учеников N, которое не меньше 10, но не превосходит
//100, каждая из следующих N строк имеет следующий формат:
//<Фамилия> <Имя> <оценки>, где <Фамилия> – строка, состоящая не 
//более чем из 20 символов, <Имя> – строка, состоящая не более чем
//из 15 символов <оценки> – через пробел три целых числа, 
//соответствующие оценкам по пятибалльной системе. <Фамилия> и 
//<Имя>, а также <Имя> и <оценки> разделены одним пробелом. 
//Пример входной строки: Иванов Петр 4 5 4
//Требуется написать программу, которая будет выводить на экран 
//фамилии и имена трех лучших по среднему баллу учеников. Если 
//среди остальных есть ученики, набравшие тот же средний балл, 
//что и один из трех лучших, то следует вывести и их фамилии и 
//имена. Требуемые имена и фамилии можно выводить в произвольном 
//порядке (8).

//Студент Шашкин Максим ПС-24
//Среда разработки PascalABC.NET
//Источник: https://informatics.msk.ru/mod/book/view.php?id=535

Program BestStudents;
const
  score = ['1' .. '5'];
type
  Stor = ^StudStor;
  StudStor = record
               FullStr: string;
               Num: integer;
               Next: Stor
             end;
var
  NameOfFile, Str: string;
  FInp, FOut: text;
  Num, Count, Max1, Max2, Max3, Marks: integer;
  Head: Stor;
  Ch: char;
  
procedure MaxValues(Num: integer);
begin
  if Num > Max3
  then
    begin
      if Num > Max2
      then
        begin
          if Num > Max1
          then
            begin
              Max3 := Max2;
              Max2 := Max1;
              Max1 := Num
            end
          else
            if Num = Max1
            then
              begin
                Max3 := Max2;
                Max2 := Max1
              end
        end
      else
        if Num = Max2
        then
          Max3 := Num
    end
end;

procedure StrToStor(Str: string; Marks: integer);
var
  NewStud: Stor;
  Temp: Stor;
begin
/////////////////////////////////////////////////////// запись в хранилище
////////////////////////////////////////////////// и нахождение максимумов
  new(NewStud);
  NewStud^.FullStr := Str;
  NewStud^.Num := Marks;
  NewStud^.Next := nil;
  MaxValues(Marks);
  if Head = nil
  then
     Head := NewStud
  else
    begin
      Temp := Head;
      while Temp^.Next <> nil
      do
        Temp := Temp^.Next;
      Temp^.Next := NewStud
    end
///////////////////////////////////////////////////////
end;
 
procedure PrintStud(var FOut: text);
var
  Temp: Stor; 
begin
  Temp := Head;
  while Temp <> nil
  do 
    begin
      
      if Temp^.Num = Max1
      then
        writeln(FOut, Temp^.FullStr, ' ', (Max1 / 3):0:2)
      else
        if Temp^.Num = Max2
        then
          writeln(FOut, Temp^.FullStr, ' ', (Max2 / 3):0:2)
        else
          if Temp^.Num = Max3
          then
            writeln(FOut, Temp^.FullStr, ' ', (Max3 / 3):0:2);
      Temp := Temp^.Next
    end  
end;
 
begin
  Max1 := 0;
  Max2 := 0;
  Max3 := 0;
  Str := '';
  Ch := '1';
  Count := 0;
  Num := 0;
  Marks := 0;
  Head := nil;
  writeln('введите название входного файла в txt ');
  readln(NameOfFile);
  assign(FInp, NameOfFile);
  
  while not fileexists(NameOfFile)
  do
    begin
      writeln('нет такого файла!');
      writeln('введите название входного файла в txt ');
      readln(NameOfFile);
      assign(FInp, NameOfFile)
    end;
  reset(FInp);
  
  writeln('введите название выходного файла в txt ');
  readln(NameOfFile);
  assign(FOut, NameOfFile);
  rewrite(FOut);
  
  while not eof(FInp) // считывание файла, обработка по символу
  do
    begin
      if not eoln(FInp)
      then
        begin
          if Num < 2
          then
            read(FInp, Ch);
          if Ch = ' ' // увеличиваем счетчик пробелов и обнуляем кол-во символов
          then
            begin
              Count := 0;
              Num := Num + 1 
            end
          else
            Count := Count + 1;
          if ((Count <= 20) and (Num = 0)) or ((Count <= 15) and (Num = 1)) // Count
          then
            Str := Str + Ch
          else
            if Num >= 2  // Count теперь как счетчик оценок, а не символов
            then
              begin
                read(FInp, Count);
                Marks := Marks + Count
              end
        end
      else
        begin
          if Str <> ''
          then
            StrToStor(Str, Marks);  // помещаем в хранилище            
          readln(FInp);
          Str := ''; // освобождаем место под другую строку
          Num := 0;
          Count := 0;
          Marks := 0
        end
    end;
  writeln('Средние баллы 3-х лучших учеников: ', (Max1 / 3):0:2, ' ', (Max2 / 3):0:2, ' ', (Max3 / 3):0:2);
  PrintStud(FOut);
  Close(FOut)
end.