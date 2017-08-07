import static java.lang.System.*;

class options {
   boolean insensitive = false;
   boolean filename_only = false;
   boolean number_lines = false;
   boolean reverse_match = false;
   String regex;
   String[] filenames;

   options (String[] args) {
      if (args.length == 0) { 
         err.printf ("Usage: %s [-ilnv] regex [filename...]%n", messages.program_name);
         exit (messages.EXIT_FAILURE);
      }
      
      if (args[0].charAt(0) == '-'){
    	  for(int i = 0;i < args[0].length();i++){
    		  char c = args[0].charAt(i);
    		  switch (c){
    		  	  case '-': break;
    		      case 'i': insensitive = true;
    		                break;
    		      case 'l': filename_only = true;
    		      			break;
    		      case 'n': number_lines = true;
    		      			break;
    		      case 'v': reverse_match = true;
    		      			break;
    		      default: err.printf("Usage: %s [-ilnv] regex [filename...]%n", 
    		    		  messages.program_name);
    		      		    break;
    		  }
    	  }
    	  
    	  regex = args[1];
    	  filenames = new String[args.length - 2];
    	  for (int argi = 2; argi < args.length; ++argi) {
    		  filenames[argi - 2] = args[argi];
    	  }
      }
      
      else {
    	  regex = args[0];
    	  filenames = new String[args.length - 1];
    	  for (int argi = 1; argi < args.length; ++argi) {
    		  filenames[argi - 1] = args[argi];
    	  }
      }
      
   }
}

