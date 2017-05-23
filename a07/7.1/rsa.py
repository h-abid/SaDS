import random

def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a


def multiplicative_inverse(a, b):
    x = 0
    y = 1
    lx = 1
    ly = 0
    oa = a 
    ob = b 
    while b != 0:
        q = a // b
        (a, b) = (b, a % b)
        (x, lx) = ((lx - (q * x)), x)
        (y, ly) = ((ly - (q * y)), y)
    if lx < 0:
        lx += ob 
    if ly < 0:
        ly += oa  
    return lx


def is_prime(num):
    if num == 2:
        return True
    if num < 2 or num % 2 == 0:
        return False
    for n in range(3, int(num**0.5)+2, 2):
        if num % n == 0:
            return False
    return True

def generate_keypair(p, q):
    if not (is_prime(p) and is_prime(q)):
        raise ValueError('Both numbers must be prime.')
    elif p == q:
        raise ValueError('p and q cannot be equal')
   
    #n = pq
    n = p * q

    phi = (p-1) * (q-1)


    #Choose an integer e such that e and phi(n) are coprime
    e = random.randrange(1, phi)

    #Use Euclid's Algorithm to verify that e and phi(n) are comprime
    g = gcd(e, phi)
    while g != 1:
        e = random.randrange(1, phi)
        g = gcd(e, phi)

    #Use Extended Euclid's Algorithm to generate the private key
    d = multiplicative_inverse(e, phi)

    while e == d:
        #Choose an integer e such that e and phi(n) are coprime
        e = random.randrange(1, phi)

        #Use Euclid's Algorithm to verify that e and phi(n) are comprime
        g = gcd(e, phi)
        while g != 1:
            e = random.randrange(1, phi)
            g = gcd(e, phi)

        #Use Extended Euclid's Algorithm to generate the private key
        d = multiplicative_inverse(e, phi)

    
    #Return public and private keypair
    #Public key is (e, n) and private key is (d, n)
    return ((e, n), (d, n))

def encrypt(pk, plaintext):
    #Unpack the key into it's components
    key, n = pk
    #Convert each letter in the plaintext to numbers based on the character using a^b mod m
    cipher = [pow(ord(char),key,n) for char in plaintext]
    #Return the array of bytes
    return cipher

def decrypt(pk, ciphertext):
    #Unpack the key into its components
    key, n = pk
    #Generate the plaintext based on the ciphertext and key using a^b mod m
    plain = [chr(pow(char, key, n)) for char in ciphertext]
    #Return the array of bytes as a string
    return ''.join(plain)

def rand_pq(n):
    high = 2**n
    low = 1

    primes = [i for i in range(1 , high) if is_prime(i)]
    p = random.choice(primes)
    q = random.choice(primes)
    while q * p < high or p == q:
        p = random.choice(primes)
        q = random.choice(primes)
    return (p,q)
    

if __name__ == '__main__':

    print "TEST1"
    message = 'whatastring'
    print "You are sending: ", message
    n = len(message)
    p,q = rand_pq(n)
    public, private = generate_keypair(p,q)

    encrypted = encrypt(public, message)
    print "The decrypted message is: ", ''.join(map(lambda x: str(x), encrypted))
    decrypted = decrypt(private, encrypted) 

    print "The decryption gives you: ", decrypted

    if (message == decrypted):
        print('The strings are the same')







