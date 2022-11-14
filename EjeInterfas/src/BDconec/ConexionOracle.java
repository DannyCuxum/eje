
package BDconec;
import java.sql.Connection;
import java.sql.DriverManager;

public class ConexionOracle {
    
    public Connection conn =null;
    private String url,user,paa,Driver;
    public Connection conn2;
    
    public ConexionOracle(){//metodo constructor de la clase cuando se instanci un objeto
        conectar();   
    }
    private void conectar(){ //metodo para la conexion a DB
        try{
            
            //inicializamos las variable de la DB
            url="jdbc:oracle:thin:@localhost:1521:orcl";
            Driver="oracle.jdbc.OracleDriver"; 
            
            user="DANYC";
            paa="123";
            conn2=null;
         
            
            //vacriable de conexion:
            Class.forName(Driver);//driver a utilizar. solo un parametr
            conn = DriverManager.getConnection(url, user, paa);//se escoje el que tenga 3 parametros
            conn2=conn;
            System.out.println("Conectado!");
            
        }catch(Exception e){
            
            System.out.println("Error al conectar la DB");
        }
    }
    
    public void desconectar(){
        
        try{
            conn.close();
            System.out.println("se Desconecto!");
        }catch(Exception e){
            
            System.out.println("Error al desconectar");
        
        }
    
    }
    
    
    
    /*crear usuario en SQL SERVER
    
    PASO 1:
    alter session set "_ORACLE_SCRIPT"=true;	//con esto podemos crear usuarios
    CREATE USER "Nombre_usuario" IDENTIFIED BY "Contraseña";//con esto se crea el user
    GRANT CONNECT, RESOURCE,DBA TO "nombre_use";//le indicamos que permite la conexion de user
    
    
    
    
    
    */
}
