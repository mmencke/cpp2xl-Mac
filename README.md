# cpp2xl-Mac
## Black Scholes implementation in C++ imported to Excel 2016 on Mac

The implementation is inspired heavily by [Antoine Savine](https://github.com/asavine/xlCppTutorial). As of now I have only figured out how to export scalar functions (with scalar input) from C++ to Excel on Mac. Only call option functions have been implemented, but it should be fairly easy to extend this to other european payoffs as well.

Developed in Xcode 9.2. The C++ project (cpp2xl.xcodeproj) contains
- blackScholes.hpp: Black-Scholes implementation
- cpp2xl.hpp: header for the Dynamic Library
- cpp2xl.cpp: main file for the Dynamic Library
- gaussians.hpp: Implementation of the Gaussian distribution functions
- monteCarlo.hpp: Implementation of Black-Scholes Monte Carlo simulations of Call options

Project is a Library with Framework: STL (C++ library) and Type: Dynamic.

libcpp2xl.dylib is the Dynamic Library itself. This is put in the folder "/Library/Application Support/Microsoft", so Excel is able to see it.

Cpp2xl.xlsm is the Macro-Enabled Excel workbook. It imports C++ functions as `BlackScholes(spot, strike, mat, rate, yield, vol)`, which is the Black-Scholes formula, `BlackScholesIV(spot, strike, mat, rate, yield, obsPrice)`, which finds Black-Scholes implicit volatility and `BlackScholesMonteCarlo(spot, strike, mat, rate, yield, vol, nPaths, nSteps)`, which runs Monte Carlo simulations for Black-Scholes call options.

## Example VBA function

The following VBA code imports `xBlackScholes` function from *cpp2xl.cpp* into Private VBA function `cppBlackScholes`

```
Private Declare PtrSafe Function cppBlackScholes _
Lib "/Library/Application Support/Microsoft/libcpp2xl.dylib" _
Alias "xBlackScholes" (ByVal spot As Double, ByVal strike As Double, ByVal mat As Double, ByVal rate As Double, ByVal yield As Double, ByVal vol As Double) As Double
```

Then we create Public VBA function `BlackScholes` that checks whether the workbook has access to the Dynamic Library before calling `cppBlackScholes`

```
Public Function BlackScholes(spot As Double, strike As Double, mat As Double, rate As Double, yield As Double, vol As Double) As Double

    If hasAccess = False Then
        hasAccess = requestFileAccess()
    End If

    If hasAccess Then
        BlackScholes = cppBlackScholes(spot, strike, mat, rate, yield, vol)
    End If

End Function
```

`hasAccess` is a boolean VBA variable. The `requestFileAccess` function can be seen below

```
Private Function requestFileAccess() As Boolean

    Dim fileAccessGranted As Boolean
    Dim filePermissionCandidates

    filePermissionCandidates = Array("/Library/Application Support/Microsoft/libcpp2xl.dylib")
    fileAccessGranted = GrantAccessToMultipleFiles(filePermissionCandidates)

    requestFileAccess = fileAccessGranted

End Function
```
