#pragma once

template<typename I> requires std::integral<I>


class rational {
    
    I num_; 
    I den_;

public:
// COSTRUTTORE DI DEFAULT

    rational() : num_(0), den_(1) {}

// COSTRUTTORE CHE INIZIALIZZA NUM_ E DEN_

    rational(I n, I d) {
		
        if (d == 0) {
            // GESTIONE NaN e Inf
            den_ = 0;
            if (n == 0) {
                num_ = 0;  // se ho 0/0 mi da NaN 
            } else if (n > 0) {
                num_ = 1;  // caso numeratore positivo mi da +Inf
            } else {
                num_ = -1; // caso numeratore negativo mi da -Inf
            }
        } 
        else {
			
			I divisore=mcd(n,d); //qua passo a mcd i valori di n e d per semplificare la frazione
			
			num_=n/divisore;
			den_=d/divisore;
            

            // Questo if mi serve per poter scrivere i numeri negativi dove spsoto il segno - sul numeratore
            if (den_ < 0) {
                num_ = -num_;
                den_ = -den_;
            }
        }
    }

    // Restituisco valori num_ e den_
    I num() const { return num_; }
    I den() const { return den_; }
	
	//ALGORIMTO EUCLIDEO per calcoalre MCD
		I mcd(I a,I b){
		a=std::abs(a);
		b=std::abs(b); //Per questo algorimo a e b devono essere positivi uso abs()
		
		
		while(b != 0) {
			I r=a % b;
			a=b;
			b=r;
		}
		return a;
	}


//OPERAZIONI
 

   // Implementazione  +=
    rational& operator+=(const rational& other) {
		
		if (num_ == 0 && den_ == 0) return *this;  //CASO NaN + numero = NaN
		if (other.num_ == 0 && other.den_ == 0) { //CASO numero + NaN = Nan
			num_ = 0; 
			den_ = 0;
			return *this; 
		}
		
		//Guardo se almeno uno è inf
		if (den_ == 0 || other.den_ == 0) {
			/*se lo sono entrambi devo guardare il segno
			Devo gestire i vari casi tenendo conto del segnbo inf+inf; inf+ -inf
			In base al segno prima con rational ho impsoto num=+1 oppure num=-1 unico caso che mi preoccupa quindi e se ho inf - inf oppure -inf + inf che da come risulttao NaN */
			
			if (den_ == 0 && other.den_ == 0) {
				
				if (num_ != other.num_){
					num_ = 0; //segni opposti mi da come risultato NaN
				}					
			}
			
			else if(other.den_ == 0) {
					*this = other;  // caso numero+inf=inf
				}
			
			return *this;
    }


		I n = (num_ * other.den_) + (other.num_ * den_); //FORMULA NUM (a*d+b*c)
        I d = den_ * other.den_; //FORMULA DEN (c*d)
        
        num_ = n;
        den_ = d;

		
		//SEMPLIFICO E GUARDO SEGNO
		if(den_ !=0){
			I divisore = mcd(num_, den_);
			num_=num_/divisore;
			den_=den_/divisore;
		}
		if (den_ < 0) { 
			num_ = -num_;
			den_ = -den_; 
		}
		
		return *this;
	}
	
	
	
	//Implementazione +
	rational operator+(const rational& other) const {
    rational ret = *this; 
    ret += other;         
    return ret;           
}
	
		
	//Implementazione -=
	 rational& operator-=(const rational& other) {
		 
		 
		 if (num_ == 0 && den_ == 0) return *this;  //CASO NaN - numero = NaN
		 if (other.num_ == 0 && other.den_ == 0) { //CASO numero - NaN = Nan
			num_ = 0; 
			den_ = 0;
			return *this; 
		}
		
		//Guardo se almeno uno è inf
		if (den_ == 0 || other.den_ == 0) {
			
		
			
			/*se lo sono entrambi devo guardare il segno
			Devo gestire i vari casi tenendo conto del segnbo inf-inf; inf- -inf
			In base al segno prima con rational ho impsoto num=+1 oppure num=-1 unico caso che mi preoccupa quindi e se ho inf - inf oppure -inf + inf che da come risulttao NaN */
			
			if (den_ == 0 && other.den_ == 0) {
				
				if (num_ == other.num_){
					num_ = 0; //Qua rispetto all'operazione di somma num e other numd evono avere lo stesso segno per darmi NaN
				}					
			}
			
			else if(other.den_ == 0) {
					num_=-other.num_;  // numero - inf = -inf
					den_=0;
				}
			
			return *this;
    }
 
        I n= (num_*other.den_)-(other.num_*den_);     //FORMULA NUM (a*d-b*c)
		
		I d=den_*other.den_;  //FORMULA DEN (c*d)
		
		num_=n;
		den_=d;
		
		//SEMPLIFICO E GUARDO SEGNO
		if(den_ !=0){
			I divisore = mcd(num_, den_);
			num_=num_/divisore;
			den_=den_/divisore;
		}
		if (den_ < 0) { 
			num_ = -num_;
			den_ = -den_; 
		}
        return *this;
    }
	
	
	
	//Implementazione -
	rational operator-(const rational& other) const {
    rational ret = *this; 
    ret -= other;         
    return ret;           
}


	//Implementazione *=
    rational& operator*=(const rational& other) {
		
		if (num_ == 0 && den_ == 0) return *this;  //CASO NaN * numero = NaN
		if (other.num_ == 0 && other.den_ == 0) { //CASO numero * NaN = Nan
			num_ = 0; 
			den_ = 0;
			return *this; 
		}
		
		//Guardo se almeno uno è inf
		
		if(den_==0 || other.den_==0){
			
			
			
			//FORMA INDETERMINATA 0*INF
			if((num_==0 && den_!=0) || (other.num_==0 && other.den_!=0)){
				num_=0;
				den_=0;
			}
			else {
				if (num_>0 && other.num_>0) {
					// inf * inf = inf   oppure caso inf*psotivo=inf
					num_ = 1;
					den_ = 0;
				}
				else if (num_<0 && other.num_<0) {
					// -inf* -inf=inf oppure caso -inf*negaivo=inf
					num_ = 1;
					den_ = 0;
				}
				else {
					// inf *-nf =nf oppure caso inf*negativo=-inf
					// oppure   -inf*positivo=-inf
					num_ = -1;
					den_ = 0;
				}
				return *this;
	
			}
		
		}

		
        I n=num_*other.num_;     //FORMULA NUM a*b
		
		I d=den_*other.den_;  //FORMULA DEN c*d
		
		num_=n;
		den_=d;
		
		//SEMPLIFICO E GUARDO SEGNO
		if(den_ !=0){
			I divisore = mcd(num_, den_);
			num_=num_/divisore;
			den_=den_/divisore;
		}
		if (den_ < 0) { 
			num_ = -num_;
			den_ = -den_; 
		}
		
		return *this;
	}
	
	//Implementazione *
	rational operator*(const rational& other) const {
        rational ret = *this;
        ret *= other; 
        return ret;
    }
	
	
	
	
		//    Implementazione /=    
    rational& operator/=(const rational& other) {
		
		if (num_ == 0 && den_ == 0) return *this;  //CASO NaN / numero = NaN
		if (other.num_ == 0 && other.den_ == 0) { //CASO numero / NaN = Nan
			num_ = 0; 
			den_ = 0;
			return *this; 
		}
		
		//FORMA INDETERMINATA INF/INF=NAN
		
		if(den_ == 0 && other.den_ == 0){
			num_=0;
			den_=0;
			return *this; 
		}

        I n = num_ * other.den_; //FORMULA NUM a*d
        I d = den_ * other.num_; //FORMULA DEN b*c

        num_ = n;
        den_ = d;
		
		//SEMPLIFICO E GUARDO SEGNO
		if(den_ !=0){
			I divisore = mcd(num_, den_);
			num_=num_/divisore;
			den_=den_/divisore;
		}
		if (den_ < 0) { 
			num_ = -num_;
			den_ = -den_; 
		}
		
		return *this;
	}
	
	//     Implementazione /
	
	rational operator/(const rational& other) const {
    rational ret = *this;
    ret /= other;
    return ret;
}
	
}; 


// OPERATORE PER LA STAMPA 

template<typename I>
std::ostream& 
operator<<(std::ostream& os, const rational<I>& r) {
	
	//Gestione dei vari casi
    if (r.den() == 0) {
        
        if (r.num() == 0) {
            os << "NaN";
        }
		
		else if (r.num() > 0) {
            os << "Inf";
        } 
		
		else{
            os << "-Inf";
        }
		
    } 
	else if(r.num()==0){ //if per migliorare l stampa nel caso in cui ho 0
		os <<"0"; //CASO 0/denomiantore da come risulttao 0
	}
	else if(r.den()==1){//if per migliorare la stampa nel caso in cui ho 1 a denominatore
		os<<r.num(); // CASO denominatore=1 da coem risultato solo il numeratore
	}
    else {
        
        os << r.num() << "/" << r.den();
    }
    return os; 
}

