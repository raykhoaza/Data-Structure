// $Id: treemap.java,v 1.13 2014-05-13 01:36:04-07 - - $
// NAME: KHOA LUONG USERNAME: KLUON7
import static java.lang.System.*;

class treemap <key_t extends Comparable <key_t>, value_t> {

   private class node {
      key_t key;
      value_t value;
      node left;
      node right;
   }
   private node root;

   private void debug_dump_rec (node tree, int depth) {
      if(tree==null){return;}
      debug_dump_rec(tree.left,depth+1);
      String space = " ";
      for(int i=0;i<depth;i++){
         System.out.print(space);
      }
      System.out.format("%s%d %s %s\n",space, depth, tree.key, 
                        tree.value);
      debug_dump_rec(tree.right, depth+1); 
   }

   private void do_visit_rec (visitor <key_t, 
                value_t> visit_fn,node tree) {
      if(tree == null) return;
      else {
         do_visit_rec(visit_fn, tree.left);
         visit_fn.visit(tree.key, tree.value);
         do_visit_rec(visit_fn, tree.right);
      }
   }

   public value_t get (key_t key) {
      node current = root;
      int compare = 0;
      while(current != null){
         compare = current.key.compareTo(key);
         if(compare == 0){return current.value;}
         if(compare < 0){current = current.right;}
         if(compare > 0){current = current.left;} 
      }
      return null;
   }

   public value_t put (key_t key, value_t value) {
      if(root==null){
         root = new node();
         root.key = key;
         root.value = value;
         return null;
      }
      node current = root;
      node oldroot = null;
      int compare = key.compareTo(current.key);
      while(current!=null){ 
         if(compare == 0){
            value_t oldvalue = current.value;
            current.value = value;
            return oldvalue;  
         }
         oldroot = current;
         if(compare>0){
            current = current.right;
         }
         else{
            current = current.left;
         }
      }
      current = new node(); 
      current.key = key;
      current.value = value;
      if(compare>0){
         oldroot.right = current; 
      }
      else{
         oldroot.left = current;
      }
      return null;       
   }

   public void debug_dump () {
      debug_dump_rec (root, 0);
   }

   public void do_visit (visitor <key_t, value_t> visit_fn) {
      do_visit_rec (visit_fn, root);
   }

}
