program binary_search_tree;

{ CS 313 Homework 2 #1}
{ Jiaqi Li }

type
   bst = ^node;
   node     = record
                val  : integer;
                left : bst;
                right: bst;
             end;

var mybst: bst; { global variable }

function empty (oldbst : bst): boolean; { return whether is stack empty }
begin
   empty := oldbst = nil;
end; { empty }

function member (oldbst : bst; n :  integer): boolean; { return whether v value is stored in the tree }
begin
   if empty(oldbst) then
      member := false
   else if oldbst^.val = n then
      member := true
   else if oldbst^.val < n then
      member := member (oldbst^.right, n)
   else
      member := member (oldbst^.left, n);
end;

procedure insert(var oldbst : bst; n :  integer); { add value to the tree }
var b : bst;
begin
   new(b);
   if empty(oldbst) then
      begin
      b^.val := n;
      oldbst := b
      end
   else
      if not member(oldbst, n) then
         begin
            b^.val := oldbst^.val;
            if n < oldbst^.val then
               begin
                  insert(oldbst^.left, n);
                  b^.right := oldbst^.right;
               end
            else
               begin
                  b^.left := oldbst^.left;
                  insert (oldbst^.right, n);
               end;
         end;
end;

procedure inorder (oldbst : bst); { print contents of bst }
begin
   if not empty(oldbst) then
   begin
   inorder(oldbst^.left);
   write(oldbst^.val, ' ');
   inorder(oldbst^.right);
   end;
end;


{ main program: }

var a, count : integer;
   check : boolean;
const size = 10;

begin
   mybst := nil;
   randomize;

   if empty(mybst) then writeln('Current binary search tree is empty');

   count := 0;

   repeat
   a := random(size);
   writeln ('insert: ', a);
   if member(mybst, a) then
      begin
      writeln ('The tree does not change -- insertion already present.');
      check := true;
      end
   else writeln('New insertion');
   insert(mybst, a);
   write ('Inorder traversal of bst:', ' ');
   inorder(mybst);
   writeln;
   writeln;
   inc(count);
   until ((count > size) and (check = true));

end.
