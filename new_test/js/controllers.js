var mainControllers = angular.module('mainControllers', []);

mainControllers.controller('OverviewController', ['$scope', function($scope) {

}]);

mainControllers.controller('MPController', ['$scope', function($scope) {

}]);

mainControllers.controller('LabController', ['$scope', function($scope) {

}]);

mainControllers.controller('OHController', ['$scope', function($scope) {

}]);

mainControllers.controller('StaffController', ['$scope', '$http', function($scope, $http) {
  $http
    .get('./data/staff.txt',
        {
          headers: {
            'Content-Type': 'application/json',
            'Cache-Control': 'max-age=0'
          }
        }
      )
    .success(function(data) {
    $scope.staff = data;
  });
}]);

mainControllers.controller('ScheduleController', ['$scope', '$http', '$sce', function($scope, $http, $sce) {
  $http.get('./data/schedule1.txt',  {
              headers: {
                'Content-Type': 'application/json',
                'Cache-Control': 'max-age=0'
              }}
  ).success(function(data) {
    $scope.schedule = data;
    $scope.days = ["Monday", "Wednesday", "Friday"];
    $scope.dontEscapeHtml = function(html) {
      return $sce.trustAsHtml(html);
    };
    // console.log($('.scrollable'));
    // $('.scrollable').perfectScrollbar('update');
  });
}]);

var labControllers = angular.module('labControllers', []);

labControllers.controller('ScheduleController', ['$scope', function($scope) {

}]);

labControllers.controller('Lab1Controller', ['$scope', function($scope) {

}]);
