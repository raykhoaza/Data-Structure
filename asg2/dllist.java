// $Id: dllist.java,v 1.37 2014-04-28 20:32:21-07 - - $
//USER: KHOA LUONG USERNAME: kluon7
class dllist {

   public enum position {FIRST, PREVIOUS, FOLLOWING, LAST};

   private class node {
      String item;
      node prev;
      node next;
   }

   private node first = null;
   private node current = null;
   private node last = null;
   //private node tmp = null;
   private int currentposition = 0;

   public void printall(){
      node tmp = first;
      while(tmp.next!=null){
         System.out.format("%s\n", tmp.item);
         tmp = tmp.next;
      }
         System.out.format("%s\n", tmp.item);
   }
   
   public void printline(){
      System.out.format("%s\n", getitem());
   }
   
   public void setposition (position pos) {
      switch (pos) {
      case FIRST: if (isempty()){break;}
                  current = first;
                  break;
      case PREVIOUS: 
         if (isempty()){break;}
         if (current.prev != null){
            current = current.prev;
            currentposition-=1;
         }
         break;
      case FOLLOWING: 
         if (isempty()){break;}
         if (current.next != null){
            current = current.next;
            currentposition+=1;
         }
         break;
      case LAST: if (isempty()){break;}
                 current = last;
                 break;
      }
   }
   
   public boolean isEnd() {
      return (current.next == null);
   }

   public boolean isempty () {
      return (current==null);
   }

   public String getitem () {
      return (current.item);
   }

   public int getposition () {
      return (currentposition);
   }

   public void delete () {
      if(current.next==null){
         current = current.prev;
         if(current!=null)
            current.next=null;
         last = current;
      }
      else if (current.prev==null){
         current = current.next;
         if(current!=null) current.prev = null;
         first = current;
      }
      else {
         current.next.prev = current.prev;
         if (current.prev!=null){
            current.prev.next = current.next;
         current = current.next;
         }
         if (current.prev == null){
            first = current;
         }
      }
      currentposition = currentposition - 1;
   }

   public void insert (String item, position pos) {
      if (isempty()){
         current = new node();
         current.item = item;
         currentposition = 0;
         first = last = current;
         currentposition = currentposition + 1;
         return;
      }
      node tmp = new node();
      tmp.item = item;
      switch (pos){
         case FIRST: setposition(pos);
                     current.prev = tmp;
                     tmp.next = current;
                     tmp.prev = null;
                     setposition(pos);
                     currentposition ++;
                     break;
         case PREVIOUS:
                        if (current.prev == null){
                           current.prev = tmp;
                           tmp.next = current;
                           tmp.prev = null; 
                           current = tmp;
                           first = tmp;
                           currentposition ++;
                        }
                        else {
                           current.prev.next = tmp;
                           tmp.prev = current.prev;
                           tmp.next = current;
                           current.prev = tmp;
                           current = tmp;
                           currentposition ++;
                        }
                        break;
         case FOLLOWING:
                         if (current.next==null){
                            current.next = tmp;
                            tmp.next = null;
                            tmp.prev = current;
                            current = tmp;
                            last = tmp;
                            currentposition ++;
                         }
                         else {
                            current.next.prev = tmp;
                            tmp.next = current.next;
                            current.next = tmp;
                            tmp.prev = current;
                            current = tmp;
                            currentposition ++;
                         }
                         break;
         case LAST: last.next = tmp;
                    tmp.prev = last;
                    tmp.next = null;
                    last = tmp;
                    current = tmp;
                    currentposition ++;
                    break;
      }
   }
}

