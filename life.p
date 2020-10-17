program Game_of_Life;
uses sysutils;

{ CS313 Homework 2 #2}
{ Jiaqi Li }

const size = 37;

type
   neighbor   = (topleft, top, topright, left, right, downleft, down, downright);
   state = array [neighbor] of boolean; { storing survival status of a given cell's neighbor}
   grid  = array[0..size, 0..size] of boolean;  {true - alive, false - dead}

var { global variables }
   g      : grid;


procedure initgrid;
var
   r, c : integer;
begin
   for r := 0 to size do
      for c := 0 to size do
         begin
         if random(2) = 1 then
         g[r][c] := true else g[r][c] := false;
         {g[r][c] := false;}
         end;
end;


procedure printgrid;
var
   r, c : integer;
begin
   for r := 0 to size do
      begin
         for c := 0 to size do
         begin
            if g[r][c] then
               write (' #') else write (' .');
         end;
         writeln;
      end;
end;

procedure updategrid;
var
   gnew : grid;
   r, c, count: integer;
   n : neighbor;
   s : state;

   procedure enum;
   {nested procedure building the array s}
   var row_de, row_in, col_de, col_in: integer;
   begin
      {finding row and column numbers as they increase or decrease by 1}
      row_de := (r + size) mod (size + 1);
      row_in := (r+1) mod (size+1);
      col_de := (c + size) mod (size + 1);
      col_in := (c+1) mod (size+1);

      {assigning survival state of neighbors}
      s[topleft] := g[row_de][col_de];
      s[top] := g[row_de][c];
      s[topright] := g[row_de][col_in];
      s[left] := g[r][col_de];
      s[right] := g[r][col_in];
      s[downleft] := g[row_in][col_de];
      s[down] := g[row_in][c];
      s[downright] := g[row_in][col_in];
   end;

begin
   gnew := g; {copying the current grid over to the new grid}
   for r := 0 to size do
      for c := 0 to size do

         begin
         count := 0;
         enum;
         for n := topleft to downright do
         begin
         if s[n] then inc (count);
         end;
         //write(count, ' ');

         if g[r][c] then
            begin
            if not ((count = 2) or (count = 3)) then
               gnew[r][c] := false;
               //writeln('true count: ', count);
            end
         else
            begin
            if count =3 then
               gnew[r][c] := true;
               //writeln('false count: ', count);
            end;
         end;

   g:= gnew; {replacing the old grid with the updated grid}
end;


{ main program -------------------- }
var
   a, r, c: integer;
begin
   randomize;
   initgrid;
   a := 0;
   c := 0;

   repeat
      for r := c to a do
      begin
         c := 1;
         writeln('Game of Life (38x38) -- Generation ', r, ':');
         printgrid;
         sleep(200);
         updategrid;
      end;
      write('How many iterations (0 to end)?');
      read(a);
   until a = 0;

end.
