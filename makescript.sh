#!/bin/bash


server(){
	if ( make -C ./Server/ )
        then
                echo " server build successfull"
		mv ./Server/server ./
        else
                echo " server buiild unsuccessfull"
        fi

}
client(){
	if ( make -C ./Client/ )
        then
                echo " client build successfull"
		mv ./Client/c1 ./
        else
                echo " client buiild unsuccessfull"
        fi
}
vendor(){
	if ( make -C ./Vendor/ )
        then
                echo " vendor build successfull"
		mv ./Vendor/adder ./
        else
                echo " vendor buiild unsuccessfull"
        fi
}

clean(){
	if ( make clean -C ./Server/ )
        then
                echo " server clean successfull"
        else
                echo " server clean unsuccessfull"
        fi

	if ( make clean -C ./Client/ )
        then
                echo " client clean successfull"
        else
                echo " client clean unsuccessfull"
        fi

	if ( make clean -C ./Vendor/ )
        then
                echo " vendor clean successfull"
        else
                echo " vendor clean unsuccessfull"
        fi

	rm adder
	rm c1
	rm server
	unlink reqFifo


}

while true
do

        echo "Enter your choice"
        echo "1.Build"
        echo "2.Clean"
        echo "3.run"
        echo "4.exit"
        read choice

        if [[ "$choice" -eq "1" ]]
        then
                echo "  build started"
                server
		client
		vendor

        elif [[ "$choice" -eq "2" ]]
        then
                echo "clean"
                clean

        elif [[ "$choice" -eq "3" ]]
        then
                echo "Running "
                #xterm  -fn "xft:DejaVu Sans Mono:pixelsize=30" -hold -e ./run
                ./server
		
                echo " "

        elif [[ "$choice" -eq "4" ]]
        then
                exit
        else
                echo "Wrong choice"
        fi

done


