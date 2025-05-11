String homePagePart1 = F(R"=====(<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1, viewport-fit=cover">
  <title>Smart Home Care System</title>
  <style>
   
    body {       
      background-color: #e7cb7c;
    } 
    .flex-Container {
      display: flex;
      flex-direction: column;
      background-color: #e7cb7c;
      align-items: center;
    }
    h1 {
      font: bold;
      font-size: 60px;
      font-family: Georgia, 'Times New Roman', Times, serif;
      color: #ba4535;
      text-align: center;
    }
    p {
      font-size: 20px;
      font-family: Georgia, 'Times New Roman', Times, serif;
      color: black;
      text-align: center;
    }
    th, td {
      font-size: 30px;
      padding: 8px;
      text-align: left;
      border-bottom: 1px solid #ffffff;
    }
  </style>
  <script>
    function fetchUltrasonic() {
      fetch('/Ultrasonic') // Call the ESP32 server
        .then(response => response.text()) // Convert response to text
        .then(sonic => {
          console.log("Ultrasonic:", sonic); // Debugging output in console
          document.getElementById("UltrasonicValue").innerText = sonic; // Update webpage
          doorStatus(parseFloat(sonic)); // Determine if door is open/closed
        })
        .catch(error => console.error('Error fetching Ultrasonic:', error)); // Handle errors
    }

    function doorStatus(distance) {
      const openEl = document.getElementById("Open");
      const closedEl = document.getElementById("Closed");

      if (distance < 15) {
        closedEl.style.display = "none";
      
      } else {
        openEl.style.display = "none";
        
      }
    }

    window.onload = () => {
      fetchUltrasonic(); // Initial fetch
      document.getElementById("Open").style.display = "none";
      document.getElementById("Closed").style.display = "none";
      setInterval(fetchUltrasonic, 1000); // Repeat every second
    };
  </script>
</head>
<body>
  <div class="container">
    <img src="grandma grandpa.png" alt="Smart Home Care System"  style="max-width: 100%; height: auto;">
    <h1>Smart Home Care System</h1>
    <p>Distance: <span id="UltrasonicValue">Loading...</span> cm</p>
    <p style="font-size: 40px; color: #91bda7" id="Open"><b>Door status: Open</b></p>
    <p style="font-size: 40px; color: #cb6341" id="Closed;"><b>Door status: Closed</b></p>
  </div>
</body>

</html>)=====");
