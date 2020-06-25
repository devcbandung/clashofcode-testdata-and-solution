s = input()
r = s[::-1] # reverse s

if (s == r):
  print('sensitive palindrome')
elif (s.lower() == r.lower()):
  print('insensitive palindrome')
else:
  print('not a palindrome')
