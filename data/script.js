document.addEventListener("DOMContentLoaded", function() {
    function loadStatus() {
        fetch('/api/status')
        .then(response => response.json())
        .then(data => {
            let statusDiv = document.getElementById('status');
            let internetPower = document.getElementById('toggleInternetPower');
            let lightPower = document.getElementById('toggleLightPower');

            statusDiv.innerHTML = `
                <p>Джерело живлення: <strong>${data.powerSource === "mains" ? "⚡" : "🔋"}</strong></p>
                <p>Заряд батареї: ${data.batteryLevel}%</p>
                <p>Напруга: ${data.batteryLevel}V</p>
                <p>Медіаконвертор: ${data.mediaConverterState.toUpperCase()}</p>
                <p>Роутер: ${data.routerState.toUpperCase()}</p>
                <p>Освітлення: ${data.lightState.toUpperCase()}</p>
                <p>Час: ${data.currentHour}:${data.currentMinute}</p>
                <p>Нічні години з ${data.startNightHourInterval}:00 по ${data.endNightHourInterval}:00</p>
            `;

            internetPower.checked = Boolean(data.mediaConverterState === "on");
            lightPower.checked = Boolean(data.lightState === "on");
        });
    }

    document.getElementById('toggleInternetPower').addEventListener('click', function() {
        fetch('/api/toggleInternetPower', { method: 'POST' })
        .then(() => loadStatus());
    });

    document.getElementById('toggleLightPower').addEventListener('click', function() {
        fetch('/api/toggleLightPower', { method: 'POST' })
        .then(() => loadStatus());
    });

    document.getElementById('setTimeBtn').addEventListener('click', function() {
        let hour = document.getElementById('hourInput').value;
        let minute = document.getElementById('minuteInput').value;

        fetch('/api/setTime', {
            method: 'POST',
            headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
            body: `hour=${encodeURIComponent(hour)};minute=${encodeURIComponent(minute)}`
        })
        .then(() => loadStatus());
    });

    document.getElementById('setSettingsBtn').addEventListener('click', function() {
        let startHour = document.getElementById('startHourInput').value;
        let endHour = document.getElementById('endHourInput').value;
        fetch('/api/setSettings', {
            method: 'POST',
            headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
            body: `startHour=${encodeURIComponent(startHour)}&endHour=${encodeURIComponent(endHour)}`
        })
        .then(() => loadStatus());
    });

    // Инициализируем статус при загрузке
    loadStatus();
});
