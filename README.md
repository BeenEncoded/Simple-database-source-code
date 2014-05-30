#Simple database  
  
The goal was to design a database that could do a few simple things.  
  
###**commands:**
  
SET [name] [value] : sets/creates a variable  
GET [name]         : prints a variable  
UNSET [name]       : deletes a variable  
NUMEQUALTO [value] : prints number of objects equal to a number  
END                : exits program  

###**Transactional commands:**

COMMIT   : commits all transaction blocks  
ROLLBACK : removes the most recent transaction block  
BEGIN    : opens a transaction block  