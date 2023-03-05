<template>
    <div id="coursesTable"></div>
</template>
 
<script>
require('timetables/exampel/Timetables.min.js');
import Timetables from 'timetables';
export default {
    name: 'CourseTable',
    data() {
        return {
            showUsualCourseDialog: false,
            showPracticeCourseDialog: false,
            selectedCourseIndex: 0
        }; 
        courseList: [
            ['大学英语(Ⅳ)@10203', '大学英语(Ⅳ)@10203', '', '', '', '', '毛概@14208', '毛概@14208', '', '', '', '选修'],
            ['', '', '信号与系统@11302', '信号与系统@11302', '模拟电子技术基础@16204', '模拟电子技术基础@16204', '', '', '', '', '', ''],
            [
                '大学体育(Ⅳ)',
                '大学体育(Ⅳ)',
                '形势与政策(Ⅳ)@15208',
                '形势与政策(Ⅳ)@15208',
                '',
                '',
                '电路、信号与系统实验',
                '电路、信号与系统实验',
                '',
                '',
                '',
                ''
            ],
            ['', '', '', '', '电装实习@11301', '电装实习@11301', '', '', '', '大学体育', '大学体育', ''],
            ['', '', '数据结构与算法分析', '数据结构与算法分析', '', '', '', '', '信号与系统', '信号与系统', '', '']
        ];
    },

    computed: {},
    created() {},
    mounted() {
        // 实例化(初始化课表)
        this.Timetable = new Timetables({
            el: '#coursesTable',
            timetables: this.courseList
            // week: week,
            // timetableType: courseType,
            // highlightWeek: day,
            // gridOnClick: function (e) {
            //     alert(e.name + '  ' + e.week + ', 第' + e.index + '节课, 课长' + e.length + '节');
            //     console.log(e);
            // },
            // styles: {
            //     Gheight: 50
            // }
        });
    },
    methods: {}
};
</script>
 
<style scoped>
</style>