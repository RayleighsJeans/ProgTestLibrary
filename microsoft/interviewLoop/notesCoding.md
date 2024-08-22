= CODING =====================================================================
  >> U -- Understand the problem
  >> M -- Match the problem with the interviewer
  >> P -- Plan your approach and solution
  >> I -- Implement your solution
  >> R -- Review your solution
  >> E -- Evaluate your solution


= UTILITY SNIPPETS ===========================================================
  >> Test kth bit is set:
     num & (1 << k) != 0
  >> Set kth bit:
    num |= (1 << k)
  >> Turn off kth bit: 
    num &= ~(1 << k)
  >> Toggle the kth bit: 
    num ^= (1 << k)
  >> To check if a number is a power of 2:
    num & num - 1 == 0.

    